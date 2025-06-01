
import sys
from threading import Lock

class shell_state():
	real_states = {
	"ST_WRNG":"wrong state",
	"ST_STRT":"start state",
	"ST_WORD":"word state",
	"ST_OPRA":"operator state",
	"ST_SEQ":"sequence state",
	"ST_LSSH":"left subshell state",
	"ST_RSSH":"right subshell state",
	"ST_HDOC":"heredoc state",
	"ST_REDR":"redirect state",
	"ST_CONT":"continue state",
	"ST_END":"ending state",
	"STATE_COUNT":"NULL STATE",
	}
	def __init__(self, state_id=0):
		self._state = list(shell_state.real_states.keys())[state_id]
		self._state_str = shell_state.real_states[self._state]
	
	def __str__(self):
		return self._state_str
	
	def __repr__(self):
		return self._state


class shell_token():
	real_types = {
	"TOK_NONE":"None type",
	"TOK_WORD":"Word",
	"TOK_PIPE":"Pipe",
	"TOK_REDIR_OUT":"Redirect out",
	"TOK_REDIR_APPEND":"Redirect append",
	"TOK_REDIR_IN":"Redirect in",
	"TOK_HEREDOC":"Heredoc",
	"TOK_AFTER":"After",
	"TOK_AND_IF":"And",
	"TOK_OR_IF":"Or",
	"TOK_LPAREN":"Left parenthesis",
	"TOK_RPAREN":"Right parenthesis",
	"TOK_AMP":"Ampersand",
	"TOK_EOF":"End of input",
	"TOK_INCOMPLETE_STRING":"INCOMPLETE STRING",
	"TOK_REDIR_FD":"Redirect fd",
	"TOK_COUNT":"INVALID TYPE",
	}
	def __init__(self, token_id, token_type_id, raw_string, hered, redir, quot, vars):
		self.id = token_id
		self._type = list(shell_token.real_types.keys())[token_type_id]
		self._type_str = shell_token.real_types[self._type]
		self.raw = raw_string
		self.hered = hered
		self.redir = redir
		self.quot = quot
		self.vars = quot

	def __repr__(self):
		return self._type

	def __str__(self):
		return self._type_str

class shell_node():
	real_types = {
	"AST_NONE":"None",
	"AST_COMMAND":"Command",
	"AST_AND":"And",
	"AST_OR":"Or",
	"AST_SEQ":"Sequence",
	"AST_PIPE":"Pipe",
	"AST_SUBSHELL":"Subshell",
	"AST_TYPE_COUNT":"INVALID TYPE",
	}
	def __init__(self,
			node_id=None,
			type_id=0,
			left_child_id=None,
			right_child_id=None,
			token_children=[],
			return_code = 0,
			cmdv = [],
			redirects = []):
		self.id = node_id
		self._type = list(shell_node.real_types.keys())[type_id]
		self._type_name = shell_node.real_types[self._type]
		self.left_child = left_child_id or None
		self.right_child = right_child_id or None
		self.token_children = token_children or None
		self.real_children = []
		self.return_code = return_code
		self.raw_string = ''
		self.cmdv = cmdv
		self.redirects = redirects

	def populate_token_lookup(self, values):
		self.real_children = []
		if self.token_children:
			for key in self.token_children:
				self.real_children.append(values[key])
			self.raw_string = ' '.join([x.raw for x in self.real_children])
		else:
			self.raw_string = self._type_name

class command_dump():
	def __init__(self):
		self.states = []
		self.tokens = {}
		self.nodes = {}
		self.raw_command = ''

	def generate_raw_command(self):
		visited = set()
		def visit(ptr):
			if ptr in visited or ptr is None or ptr not in self.nodes.keys():
				return ""
			visited.add(ptr)
			return visit(self.nodes[ptr].left_child) +" "+ self.nodes[ptr].raw_string +" "+ visit(self.nodes[ptr].right_child)
		self.raw_command = visit(list(self.nodes.keys())[0])

	def populate(self):
		for node in list(self.nodes.values()):
			print(self.tokens)
			print(node.token_children)
			node.populate_token_lookup(self.tokens)
		self.generate_raw_command()


class shell_dump():
	data_type = [
	"DT_NONE",
	"DT_STATE",
	"DT_TOKEN_INFO",
	"DT_TOKEN",
	"DT_NODES",
	"DT_REDR",
	"DT_DONE",
	"DT_COUNT",
	]
	def __init__(self, path=None, filedes=None):
		if path is None and filedes is None:
			filedes = sys.stdin.buffer
		if path is not None and filedes is not None:
			raise ValueError("Pass either path or filedes, not both")
		if path:
			try:
				self.filedes = open(path, "rb")
			except Exception as e:
				print("unable to open file:", e)
				self.filedes = None
				return
		else:
			self.filedes = filedes

		self.com_lock = Lock()
		self.commands = []
		self.com_count = 0

	@property
	def command_count(self):
		val = 0 
		self.com_lock.acquire_lock()
		val = len(self.commands)
		self.com_lock.release_lock()
		return (val)


	def _add_command(self, command):
		if type(command) != command_dump:
			return
		command.populate()
		self.com_lock.acquire_lock()
		self.commands.append(command)
		self.com_count = len(self.commands)
		self.com_lock.release_lock()

	def _read(self):
		current_command = None
		while True:
			header = self.filedes.read(4)
			if not header:
				break 
			dt = int.from_bytes(header, 'little')
			if shell_dump.data_type[dt] == "DT_STATE": # when we find a state we create a new command dump
				if current_command:
					self._add_command(current_command)
				print("new command")
				current_command = command_dump()
				state_count = int.from_bytes(self.filedes.read(4), 'little')
				for _ in range(state_count // 4):
					current_command.states.append(shell_state(int.from_bytes(self.filedes.read(4), 'little')))
			elif shell_dump.data_type[dt] == "DT_TOKEN":
				token = self._read_token()
				current_command.tokens[token.id] = token
			elif shell_dump.data_type[dt] == "DT_NODES":
				node = self._read_node()
				current_command.nodes[node.id] = node
			elif shell_dump.data_type[dt] == "DT_DONE":
				if current_command:
					self._add_command(current_command)
				current_command = None
			else:
				raise ValueError("Wrong initial data type")
		if current_command:
			self._add_command(current_command)

	def _read_token(self):
		#we have read the header
		byte_count_raw = self.filedes.read(4)
		byte_count = int.from_bytes(byte_count_raw, 'little')
		token_id_raw = self.filedes.read(8)
		token_type_raw = self.filedes.read(4)
		string_data = b""
		while True:
			raw_byte = self.filedes.read(1)
			if raw_byte == b'\x00':
				break
			string_data += raw_byte
		string_data = string_data.decode()
		token_heredoc_raw = self.filedes.read(4)
		token_redr_raw = self.filedes.read(4)
		token_quotes_removed_raw = self.filedes.read(4)
		token_variables_raw = self.filedes.read(4)
		return shell_token(
			token_id=int.from_bytes(token_id_raw, 'little'),
				token_type_id=int.from_bytes(token_type_raw, 'little'),
			raw_string=string_data,
			redir=int.from_bytes(token_redr_raw, 'little'),
			hered=int.from_bytes(token_heredoc_raw, 'little'),
			quot=int.from_bytes(token_quotes_removed_raw, 'little'),
			vars=int.from_bytes(token_variables_raw, 'little')
		)

	def _read_str(self):
		string_data = b""
		while True:
			raw_byte = self.filedes.read(1)
			if raw_byte == b'\x00':
				break
			string_data += raw_byte
		string_data = string_data.decode()
		return (string_data)

	def _read_node(self):
		self.filedes.read(4)
		ptr_raw = self.filedes.read(8)
		ptr_id = int.from_bytes(ptr_raw, 'little')

		type_raw = self.filedes.read(4)
		type_ = int.from_bytes(type_raw, 'little')

		left = int.from_bytes(self.filedes.read(8), 'little')
		right = int.from_bytes(self.filedes.read(8), 'little')

		tok_count = int.from_bytes(self.filedes.read(4), 'little')

		tokens = []
		for _ in range(tok_count):
			tok_ptr = int.from_bytes(self.filedes.read(8), 'little')
			tokens.append(tok_ptr)
		self.filedes.read(8)  # Skip NULL terminator

		ret_code = int.from_bytes(self.filedes.read(4), 'little')
		cmdv = []
		cmdv_count = int.from_bytes(self.filedes.read(4), 'little')
		for _ in range(cmdv_count):
			cmdv.append(self._read_str())
		
		redirects = []
		redirect_count = int.from_bytes(self.filedes.read(4), 'little')
		for _ in range(redirect_count):
			int.from_bytes(self.filedes.read(4), 'little')
			redr = []
			redr_type = int.from_bytes(self.filedes.read(4), 'little')
			redr_subtype = int.from_bytes(self.filedes.read(4), 'little')
			redr.append(redr_type)
			redr.append(redr_subtype)
			if (redr_subtype == 0):
				redr.append(self._read_str())
				redr.append(int.from_bytes(self.filedes.read(4), 'little'))
			else:
				redr.append(int.from_bytes(self.filedes.read(4), 'little'))
				redr.append(int.from_bytes(self.filedes.read(4), 'little'))
			redirects.append(redr)

		return shell_node(
			node_id=ptr_id,
			type_id=type_,
			left_child_id=left,
			right_child_id=right,
			token_children=tokens,
			return_code=ret_code,
			cmdv=cmdv,
			redirects=redirects
		)


def main():
	path = "test"
	x = shell_dump(path = path)
	x._read()
	print(x.commands)

if __name__ == "__main__":
	main()
