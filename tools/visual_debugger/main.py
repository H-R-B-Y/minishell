import copy
import tkinter as tk
import data_file
from threading import Thread
from  tkinter import ttk
import networkx as nx
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg

def hierarchy_pos(G, root, width=1.0, vert_gap=0.2, vert_loc=0, xcenter=0.5, pos=None, parent=None):
	"""
	A layout for a directed tree using recursion.
	Based on Joel's answer here: https://stackoverflow.com/a/29597209/1462707
	"""
	if pos is None:
		pos = {root: (xcenter, vert_loc)}
	else:
		pos[root] = (xcenter, vert_loc)
	children = list(G.successors(root))
	if not children:
		return pos
	dx = width / len(children)
	nextx = xcenter - width / 2 - dx / 2
	for child in children:
		nextx += dx
		pos = hierarchy_pos(G, child, width=dx, vert_gap=vert_gap,
							vert_loc=vert_loc - vert_gap, xcenter=nextx, pos=pos, parent=root)
	return pos

class fsm_diagram ():
	nodes = list(data_file.shell_state.real_states.keys())
	edges = [
	{"src":"ST_STRT", "dest":"ST_LSSH"},
	{"src":"ST_STRT", "dest":"ST_REDR"},
	{"src":"ST_STRT", "dest":"ST_HDOC"},
	{"src":"ST_STRT", "dest":"ST_WORD"},
	{"src":"ST_WORD", "dest":"ST_OPRA"},
	{"src":"ST_WORD", "dest":"ST_SEQ"},
	{"src":"ST_WORD", "dest":"ST_END"},
	{"src":"ST_WORD", "dest":"ST_WORD"},
	{"src":"ST_WORD", "dest":"ST_REDR"},
	{"src":"ST_WORD", "dest":"ST_RSSH"},
	{"src":"ST_WORD", "dest":"ST_HDOC"},
	{"src":"ST_WORD", "dest":"ST_WORD"},
	{"src":"ST_REDR", "dest":"ST_WORD"},
	{"src":"ST_HDOC", "dest":"ST_WORD"},
	{"src":"ST_OPRA", "dest":"ST_REDR"},
	{"src":"ST_OPRA", "dest":"ST_LSSH"},
	{"src":"ST_OPRA", "dest":"ST_WORD"},
	{"src":"ST_OPRA", "dest":"ST_CONT"},
	{"src":"ST_OPRA", "dest":"ST_HDOC"},
	{"src":"ST_CONT", "dest":"ST_STRT"},
	{"src":"ST_LSSH", "dest":"ST_WORD"},
	{"src":"ST_LSSH", "dest":"ST_REDR"},
	{"src":"ST_LSSH", "dest":"ST_HDOC"},
	{"src":"ST_LSSH", "dest":"ST_LSSH"},
	{"src":"ST_LSSH", "dest":"ST_END"},
	{"src":"ST_RSSH", "dest":"ST_END"},
	{"src":"ST_RSSH", "dest":"ST_RSSH"},
	{"src":"ST_RSSH", "dest":"ST_OPRA"},
	{"src":"ST_RSSH", "dest":"ST_SEQ"},
	{"src":"ST_RSSH", "dest":"ST_REDR"},
	{"src":"ST_RSSH", "dest":"ST_HDOC"},
	{"src":"ST_RSSH", "dest":"ST_WORD"},
	{"src":"ST_SEQ", "dest":"ST_END"},
	{"src":"ST_SEQ", "dest":"ST_WORD"},
	{"src":"ST_SEQ", "dest":"ST_REDR"},
	{"src":"ST_SEQ", "dest":"ST_HDOC"},
	{"src":"ST_SEQ", "dest":"ST_RSSH"},
	{"src":"ST_SEQ", "dest":"ST_LSSH"},
	{"src":"ST_END", "dest":"ST_STRT"},
	]
	def __init__(self, master):
		self.diag = nx.DiGraph()
		f , a = plt.subplots(figsize=[13,8], dpi=100) # this should probably be passed in
		self.fig : plt.Figure = f
		self.axis : plt.Axes = a
		self.master = master
		self.canvas = FigureCanvasTkAgg(self.fig, master = master)
		self.tkcanvas.bind("<Configure>", self.on_resize)
		self.tkcanvas.pack(fill=tk.BOTH, expand=True)
		for node in fsm_diagram.nodes:
			self.diag.add_node(node, label=node)
		for edge in fsm_diagram.edges:
			self.diag.add_edge(edge["src"], edge["dest"])
		self.layout = nx.shell_layout(self.diag)
		self.__node_colour = ['skyblue', 'red']
		self.__highlighted_node = None
		self.node_colormap = [self.__node_colour[0] for _ in list(self.diag.nodes)]
		self.__edge_colour = ['black', 'red']
		self.__highlighted_edge = None
		self.edge_colormap = [self.__edge_colour[0] for _ in list(self.diag.edges)]

		self.__state_path = None
		self.__state_path_index = 0

	@property
	def state_path(self):
		return self.__state_path
	
	@state_path.setter
	def state_path(self, value):
		try:
			l =  list(value)
			assert all([i._state in self.nodes for i in l]) and l[0]._state in self.nodes
			self.__state_path = [i._state for i in l]
		except Exception as e:
			print(f"Unable to set state path to object: {value}")
			return 
		self.state_path_index = 0

	@property
	def state_path_index(self):
		return self.__state_path_index

	@state_path_index.setter
	def state_path_index(self, value):
		if self.state_path == None:
			return
		assert type(value) == int
		assert value < len(self.__state_path)
		assert value >= 0
		self.__state_path_index = value
		dest = self.nodes[self.nodes.index(self.state_path[value])]
		self.highlight_node(dest)
		if value > 0:
			src = self.nodes[self.nodes.index(self.state_path[value - 1])]
			try:
				self.highlight_edge({"src":src,"dest":dest})
			except AssertionError as e:
				print(f"Invalid transition from {src} to {dest}")
		else:
			self.highlight_edge(None)

	@property
	def current_state(self):
		return self.nodes[
			self.nodes.index(self.state_path[self.state_path_index])]

	@property
	def current_edge(self):
		if self.__state_path_index <= 0:
			return None
		src = self.current_state
		dest = self.nodes[
			self.nodes.index(self.state_path[self.__state_path_index - 1])]
		return ({"src":dest,"dest":src})

	@property
	def node_colour(self):
		return self.__edge_colour
	
	@node_colour.setter
	def node_colour(self, val):
		try:
			l = list(val)
			assert len(l) == 2
			self.__node_colour = l
			self.node_colormap = [
				self.__node_colour[self.current_state == this]
				for this in list(self.diag.nodes)
			]
			self.redraw()
		except Exception as e:
			print(f"Unable to set value of node colour to {val}")
		return 
	
	@property
	def edge_colour(self):
		return self.__edge_colour
	
	@edge_colour.setter
	def edge_colour(self, val):
		try:
			l = list(val)
			assert len(l) == 2
			self.__edge_colour = l
			self.edge_colormap = [
				self.__edge_colour[self.current_state == this]
				for this in list(self.diag.edges)
			]
			self.redraw()
		except Exception as e:
			print(f"Unable to set value of edge colour to {val}")
		return 

	@property
	def tkcanvas(self):
		return self.canvas.get_tk_widget()

	def redraw(self):
		self.axis.clear()
		nx.draw(self.diag, self.layout, self.axis,
			node_color=self.node_colormap,
			with_labels=True, node_size=3000,
			edge_color=self.edge_colormap
		)
		# nx.draw_networkx()
		self.fig.tight_layout()
		self.axis.axis("off")
		self.canvas.draw()

	def highlight_node(self, node_name):
		if node_name == None:
			self.node_colormap = [self.__node_colour[0] for _ in self.nodes]
			self.redraw()
			return 
		assert node_name in self.nodes
		index = self.nodes.index(node_name)
		self.__highlighted_node = index
		self.node_colormap = [
			self.__node_colour[self.current_state == this]
			for this in list(self.diag.nodes)
		]
		self.redraw()

	def highlight_edge(self, edge):
		print(list(self.diag.edges))
		if edge == None:
			self.edge_colormap = [self.__edge_colour[0] for _ in self.edges]
			self.redraw()
			return 
		assert edge in self.edges
		index = self.edges.index(edge)
		self.__highlighted_edge = index
		print((self.current_edge["src"], self.current_edge["dest"]))
		self.edge_colormap = [
			self.__edge_colour[(self.current_edge["src"], self.current_edge["dest"]) == this]
			for this in list(self.diag.edges)
		]
		self.redraw()

	def on_resize(self, event):
		width = event.width
		height = event.height
		self.fig.set_size_inches(width / 100, height / 100)
		self.redraw()

	def walk_state_path(self):
		if self.__state_path_index < len(self.state_path) - 1:
			self.state_path_index = self.state_path_index + 1
		return
	
	def reverse_walk_state_path(self):
		if self.__state_path_index > 0:
			self.state_path_index = self.state_path_index - 1
		return 


class token_viewer(tk.PanedWindow):

	class token():
		def __init__(self, type, raw, *args, **kwargs):
			self.type = type
			self.raw = raw
			self.data = kwargs

	def __init__(self, master):
		super().__init__(master=master, orient=tk.HORIZONTAL, sashrelief=tk.RAISED)
		self._current_token_list = []
		
		self.left_pane = ttk.Frame(master=self)
		self.scrollbar = tk.Scrollbar(self.left_pane, orient=tk.VERTICAL)
		self.listbox = tk.Listbox(self.left_pane,
				yscrollcommand=self.scrollbar.set,
				width = 25, exportselection=False)
		self.scrollbar.config(command=self.listbox.yview)
		self.listbox.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
		self.scrollbar.pack(side=tk.RIGHT, fill=tk.Y)
		self.listbox.bind("<<ListboxSelect>>", self.on_token_selected)
		self.add(self.left_pane)

		self.right_pane = tk.Frame(master=self, background="grey", padx=10, pady=10)
		self.detail_tab = None
		self.add(self.right_pane)

	def clear_detail_pane(self):
		if self.detail_tab == None:
			return
		self.detail_tab.destroy()

	def set_detail_pane(self, item):
		if item not in self._current_token_list:
			self.clear_detail_pane()
			return
		self.detail_tab = tk.Frame(master = self.right_pane, background="white", padx=10, pady=10)
		self.detail_tab.pack(fill=tk.BOTH, expand=True)
		type_string = tk.Label(master = self.detail_tab, text=f"Type : {item._type}")
		type_string.pack(anchor=tk.W)
		data_string = tk.Label(master = self.detail_tab, text=f"Raw : {item.raw}")
		data_string.pack(anchor=tk.W)

	def on_token_selected(self, event):
		selection = self.listbox.curselection()
		self.clear_detail_pane()
		if not selection:
			return
		index = selection[0]
		item = self._current_token_list[index]
		self.set_detail_pane(item)
		return 

	@property
	def token_list(self):
		return self._current_token_list

	@token_list.setter
	def token_list(self, value):
		assert type(value) == list
		assert all([type(c) == data_file.shell_token for c in value]) and type(value[0]) == data_file.shell_token
		self._current_token_list = value
		self.listbox.delete(0, tk.END)
		for tok in value:
			self.listbox.insert(tk.END, tok.raw)

class ast_viewer(tk.Frame):
	def __init__(self, master):
		super().__init__(master=master)
		self.graph = None
		self.canvas = None
		self.figure = None
		self.ax = None

		self.init_canvas()

	def init_canvas(self):
		self.figure, self.ax = plt.subplots()
		self.canvas = FigureCanvasTkAgg(self.figure, master=self)
		self.canvas.get_tk_widget().pack(fill=tk.BOTH, expand=True, padx=10, pady=10)
		self.ax.axis("off")

	def clear(self):
		self.ax.clear()
		self.ax.set_axis_off()
		self.figure.tight_layout()
		self.canvas.draw()

	def set_ast(self, node_map, root_ptr):
		"""
		node_map: dict of ast_node {id(ptr string) : ast_node}
		root_ptr: id of root node (e.g. "0x1") (pointer string)
		"""
		self.clear()
		self.graph = nx.DiGraph()
		visited = set()

		def visit(ptr):
			if ptr in visited or ptr not in node_map:
				return
			visited.add(ptr)
			node = node_map[ptr]
			self.graph.add_node(ptr, label=node.raw_string)
			if node.left_child:
				self.graph.add_edge(ptr, node.left_child)  # ← Add edge
				visit(node.left_child)
			if node.right_child:
				self.graph.add_edge(ptr, node.right_child)  # ← Add edge
				visit(node.right_child)

		visit(root_ptr)

		# Draw
		pos = hierarchy_pos(self.graph, root_ptr)
		labels = nx.get_node_attributes(self.graph, 'label')
		nx.draw(self.graph, pos, ax=self.ax, labels=labels,
				with_labels=True, arrows=True, node_size=1000, node_color='lightgray')
		self.ax.set_axis_off()
		self.figure.tight_layout()
		self.canvas.draw()


class	node_details(tk.PanedWindow):
	def __init__(self, master):
		super().__init__(master, orient=tk.HORIZONTAL, sashrelief=tk.RAISED)
		
		# Left Pane with Listbox
		self.left_pane = ttk.Frame(self)
		self.scrollbar = tk.Scrollbar(self.left_pane, orient=tk.VERTICAL)
		self.listbox = tk.Listbox(self.left_pane,
								yscrollcommand=self.scrollbar.set,
								width=25, exportselection=False)
		self.scrollbar.config(command=self.listbox.yview)

		self.listbox.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
		self.scrollbar.pack(side=tk.RIGHT, fill=tk.Y)
		self.listbox.bind("<<ListboxSelect>>", self.on_node_select)
		self.add(self.left_pane)

		# Right Pane with Detail Display
		self.right_pane = tk.Frame(self)
		self.add(self.right_pane)

		self.detail_window = tk.Frame(self.right_pane, background="grey", padx=10, pady=10)
		self.detail_window.pack(fill=tk.BOTH, expand=True)

		# Use grid for better alignment in detail_window
		self.node_type_detail = tk.Label(self.detail_window, text="Node Type:")
		self.node_type_detail.grid(row=0, column=0, sticky='w', pady=2)

		self.left_node_detail = tk.Label(self.detail_window, text="Left Node:")
		self.left_node_detail.grid(row=1, column=0, sticky='w', pady=2)

		self.right_node_detail = tk.Label(self.detail_window, text="Right Node:")
		self.right_node_detail.grid(row=2, column=0, sticky='w', pady=2)

		self.return_code_detail = tk.Label(self.detail_window, text="Return Code:")
		self.return_code_detail.grid(row=3, column=0, sticky='w', pady=2)

		# cmdv Listbox in a sub-frame
		self.node_cmdv_detail = tk.Frame(self.detail_window, background="grey")
		self.node_cmdv_detail.grid(row=4, column=0, sticky='w', pady=(10, 2))

		label1 = tk.Label(self.node_cmdv_detail, text="cmdv:")
		label1.pack(anchor='w')

		self.cmdv_view = tk.Listbox(self.node_cmdv_detail, height=4)
		self.cmdv_view.pack(fill=tk.X, expand=True)

		# Redirects Treeview in a sub-frame
		self.redirect_area = tk.Frame(self.detail_window, background="grey")
		self.redirect_area.grid(row=5, column=0, sticky='nsew', pady=(10, 2))

		label2 = tk.Label(self.redirect_area, text="Redirects:")
		label2.pack(anchor='w')

		self.node_redirect_detail = ttk.Treeview(self.redirect_area, columns=("name", "value"), show="headings", height=4)
		self.node_redirect_detail.pack(fill=tk.X, expand=True)

		self.node_redirect_detail.heading("name", text="Name")
		self.node_redirect_detail.heading("value", text="Value")
		self.node_redirect_detail.column("name", width=100)
		self.node_redirect_detail.column("value", width=100)

		# Allow grid cell to expand
		self.detail_window.grid_rowconfigure(5, weight=1)
		self.detail_window.grid_columnconfigure(0, weight=1)

	@property
	def current_node(self):
		return self._current_node

	@current_node.setter
	def current_node(self, value):
		assert value == None or type(value) == data_file.shell_node
		if value == None and self._current_node != None:
			self.node_type_detail.configure(text="Node Type: ")
			self.left_node_detail.configure(text="Left Node: ")
			self.right_node_detail.configure(text="Right Node: ")
			self.return_code_detail.configure(text="Return Code: ")
			self.cmdv_view.delete(0, tk.END)
			self.node_redirect_detail.delete(*self.node_redirect_detail.get_children())
		if value != None:
			self.node_type_detail.configure(text=f"Node Type: {value._type_name}")
			self.left_node_detail.configure(text=f"Left Node: {value.left_child}")
			self.right_node_detail.configure(text=f"Right Node: {value.right_child}")
			self.return_code_detail.configure(text=f"Return Code: {value.return_code}")
			self.cmdv_view.delete(0, tk.END)
			for item in value.cmdv:
				self.cmdv_view.insert(tk.END, item)
			self.node_redirect_detail.delete(*self.node_redirect_detail.get_children())
			for redr in value.redirects:
				self.node_redirect_detail.insert("", tk.END, values=redr[2:])
		self._current_node = value

	@property
	def node_list(self):
		return self._node_list
	
	@node_list.setter
	def node_list(self, value):
		self.listbox.delete(0, tk.END)
		self._node_list = value
		if len(value) > 0 and all([type(x) == data_file.shell_node for x in value])\
			and type(value[0]) == data_file.shell_node:
			self._node_list = value
			for n in value:
				self.listbox.insert(tk.END, n.raw_string)

	def on_node_select(self, event):
		selection = self.listbox.curselection()
		if not selection:
			return
		index = selection[0]
		item = self._node_list[index]
		self.current_node = item


class	dbg_command_list(ttk.PanedWindow):
	def __init__(self, master):
		super().__init__(master,orient=tk.HORIZONTAL)
		self.command_selector_frame = tk.Frame(self)
		self.add(self.command_selector_frame)

		# self.command_selector_frame.configure(width=150)

		self.scrollbar = tk.Scrollbar(self.command_selector_frame, orient=tk.VERTICAL)
		self.listbox = tk.Listbox(self.command_selector_frame,
				yscrollcommand=self.scrollbar.set,
				width = 25, exportselection=False)
		self.scrollbar.config(command=self.listbox.yview)
		self.listbox.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
		self.scrollbar.pack(side=tk.RIGHT, fill=tk.Y)
		self.listbox.bind("<<ListboxSelect>>", self.on_command_selected)

		self.command_details_frame = tk.Frame(self)
		self.add(self.command_details_frame)
		self.open_when_file = []
		self.panes_shown = 0
		self._current_commands = []
		self._init_right_side()

	def _init_right_side(self):
		self.frame_frame = ttk.Notebook(master = self.command_details_frame, width=1200, height=800)
		self.frame_frame.pack(fill=tk.BOTH, expand=True)

		# Second frame
		self.fsm_frame = ttk.Frame(master = self.frame_frame)
		self.open_when_file.append((self.fsm_frame, "Finite state machine"))
		# self.frame_frame.add(self.fsm_frame, text="View fsm")
		self.open_when_file.append((self.fsm_frame, "View fsm"))
		self.fsm_skipthrough = tk.Frame(master=self.fsm_frame, height=40)
		self.fsm_skipthrough.pack(side=tk.BOTTOM)
		self.fsm = fsm_diagram(master = self.fsm_frame)

		self.fsm.tkcanvas.pack(side=tk.TOP)
		self.fsm.tkcanvas.bind("<Configure>", self.fsm.on_resize)

		self.walk_forward_button = tk.Button(master=self.fsm_skipthrough,
								text="Forward", command=self.walk_forward)
		self.walk_backwards_button = tk.Button(master=self.fsm_skipthrough,
								text="Backwards", command=self.walk_backwards)
		self.walk_label = tk.Label(master=self.fsm_skipthrough, text="")
		self.walk_backwards_button.pack(side=tk.LEFT)
		self.walk_label.pack(side=tk.LEFT, padx=50)
		self.walk_forward_button.pack(side=tk.LEFT)

		# third frame
		self.token_viewer = token_viewer(self.frame_frame)
		self.open_when_file.append((self.token_viewer, "Token viewer"))
		# self.frame_frame.add(self.token_viewer, text = "mysterious third option")
		self.open_when_file.append((self.token_viewer,"mysterious third option"))

		# self.token_viewer.token_list = list(self.data.commands[0].tokens.values())

		# fourth frame
		self.ast_viewer = ast_viewer(self.frame_frame)
		self.open_when_file.append((self.ast_viewer, "AST viewer"))
		# self.frame_frame.add(self.ast_viewer, text = "AST viewer")

		# fifth frame
		self.node_details = node_details(self.frame_frame)
		self.open_when_file.append((self.node_details, "Node viewer"))
		
	@property
	def current_commands(self):
		return self._current_commands
	
	@current_commands.setter
	def current_commands(self, value):
		if type(value) != list and not all([type(v) == data_file.command_dump for v in value]):
			raise ValueError("Invalid command values")
		self._current_commands = value
		self.listbox.delete(0, tk.END)
		for command in value:
			self.listbox.insert(tk.END, command.raw_command)
		
	def on_command_selected(self, event):
		index = self.listbox.curselection()
		if not index:
			return
		command = self._current_commands[index[0]]
		if command:
			if not self.panes_shown:
				for frame, name in self.open_when_file:
					self.frame_frame.add(frame, text = name)
			self.fsm.state_path = command.states
			self.token_viewer.token_list = list(command.tokens.values())
			self.ast_viewer.set_ast(command.nodes, list(command.nodes.keys())[0])
			self.node_details.node_list = list(command.nodes.values())

	def walk_forward(self, *a, **b):
		if self.fsm.state_path == None:
			return
		self.fsm.walk_state_path()
		if self.fsm.state_path_index > 0:
			self.walk_label.configure(text=self.fsm.current_edge)
		else:
			self.walk_label.configure(text=self.fsm.current_state)
		self.fsm.redraw()
		return

	def walk_backwards(self, *a, **b):
		if self.fsm.state_path == None:
			return
		self.fsm.reverse_walk_state_path()
		if self.fsm.state_path_index > 0:
			self.walk_label.configure(text=self.fsm.current_edge)
		else:
			self.walk_label.configure(text=self.fsm.current_state)
		self.fsm.redraw()
		return


class visual_debugger(tk.Tk):
	def __init__(self, filedes=None):
		super().__init__()
		super().title("Minishell visual debugger")
		self.bind("<Destroy>", lambda event, *a, **b: (self._data_thread.join() and sys.exit(0)) if event.widget == self else 0)

		self.current_file = "None"
		self.data = data_file.shell_dump(filedes=filedes)

		self.main_frame = tk.Frame()
		self.main_frame.pack(fill=tk.BOTH, expand=True)
		self.command_frame = dbg_command_list(self.main_frame)
		self.command_frame.pack(fill=tk.BOTH, expand=True)
		self._comcount = 0
		self._commands = []
		self._data_thread = Thread(None, self.read_thread)
		self._data_thread.start()
		self.after(100, self.update_loop)

	def update_loop(self, *a, **b):
		if self.data.command_count != self._comcount:
			self._commands = copy.copy(self.data.commands[0:self.data.command_count])
			self._comcount = len(self._commands)
		if self._commands != self.command_frame.current_commands:
			self.command_frame.current_commands = self._commands
		self.after(1000, self.update_loop)

	def read_thread(self):
		# must be run in a thread
		self.data._read()



root = visual_debugger(open("testfile", "rb"))



root.mainloop()
