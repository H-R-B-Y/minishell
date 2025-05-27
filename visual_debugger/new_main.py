import random
import tkinter as tk
from  tkinter import ttk
import networkx as nx
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg


class fsm_diagram ():
	nodes = [
	"ST_WRNG",
	"ST_STRT",
	"ST_WORD",
	"ST_OPRA",
	"ST_SEQ",
	"ST_LSSH",
	"ST_RSSH",
	"ST_HDOC",
	"ST_REDR",
	"ST_CONT",
	"ST_END",
	"STATE_COUN",
	]
	edges = [
	{"src":		"ST_STRT", "dest":"ST_LSSH"},
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
			assert all([i in self.nodes for i in l]) and l[0] in self.nodes
			self.__state_path = l
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
		if self.__state_path_index < len(self.state_path):
			self.state_path_index = self.state_path_index + 1
		return
	
	def reverse_walk_state_path(self):
		if self.__state_path_index > 0:
			self.state_path_index = self.state_path_index - 1
		return 
			

class visual_debugger(tk.Tk):
	def __init__(self):
		super().__init__()
		super().title("Minishell visual debugger")
		self.bind("<Destroy>", lambda *a, **b: exit(0))

		self.current_file = "None"

		# top bar
		self.top_frame = tk.Frame(master = self)
		self.top_frame.pack(fill=tk.X, expand=True)

		self.frame_frame = ttk.Notebook(master = self)
		self.frame_frame.pack(fill=tk.BOTH, expand=True)

		self.open_when_file = []
		# first frame
		self.inputfile_frame = ttk.Frame(master = self.frame_frame)
		self.frame_frame.add(self.inputfile_frame, text = "Select file")

		# Second frame
		self.fsm_frame = ttk.Frame(master = self.frame_frame)
		self.open_when_file.append((self.fsm_frame, "Finite state machine"))
		#self.frame_frame.add(self.fsm_frame, text="View fsm")
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
		self.token_viewer = ttk.Frame(master = self.frame_frame)
		self.open_when_file.append((self.token_viewer, "Token viewer"))
		#self.frame_frame.add(self.token_viewer, text = "mysterious third option")

	def walk_forward(self, *a, **b):
		if self.current_file == None or self.fsm.state_path == None:
			return
		self.fsm.walk_state_path()
		if self.fsm.state_path_index > 0:
			self.walk_label.configure(text=self.fsm.current_edge)
		else:
			self.walk_label.configure(text=self.fsm.current_state)
		self.fsm.redraw()
		return

	def walk_backwards(self, *a, **b):
		if self.current_file == None or self.fsm.state_path == None:
			return
		self.fsm.reverse_walk_state_path()
		if self.fsm.state_path_index > 0:
			self.walk_label.configure(text=self.fsm.current_edge)
		else:
			self.walk_label.configure(text=self.fsm.current_state)
		self.fsm.redraw()
		return

root = visual_debugger()



root.mainloop()
