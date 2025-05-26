import tkinter as tk
import networkx as nx
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg

class FSM(nx.DiGraph):
	def __init__(self, nodes=[], edges=[]):
		super().__init__()
		self.my_node_names=nodes
		self.my_edges=edges
		self.my_node_labels = None
		for node in self.my_node_names:
			super().add_node(node)
		for edge in edges:
			assert edge["src"] in self.my_node_names
			assert edge["dest"] in self.my_node_names
			super().new_edge(edge["src"], edge["dest"], label=getattr(edge, "name"))

	def new_node(self, name):
		assert name not in self.my_node_names
		self.my_node_names.append(name)
		self.add_node(name)

	def new_edge(self, src, dest, name=""):
		assert src in self.my_node_names
		assert dest in self.my_node_names
		self.my_edges.append({"src":src,"dest":dest,"name":name})
		super().add_edge(src, dest, label=name)
	
	def create_vis(self, fig, ax):
		self.my_pos = nx.shell_layout(self)
		# Draw FSM with edge labels
		nx.draw(fsm, self.my_pos, ax=ax, with_labels=True, node_color='skyblue', node_size=2000, font_weight='bold')
		edge_labels = nx.get_edge_attributes(fsm, 'label')
		nx.draw_networkx_edge_labels(fsm, self.my_pos, edge_labels=edge_labels, ax=ax)
		self.my_node_labels = nx.get_node_attributes(self, 'label')
		ax.axis('off')

	def highlight_state(self, state_name, fig, ax, canvas):
		print(self.my_node_names)
		assert state_name in self.my_node_names
		ax.clear()
		color_map = ['green' if nm == state_name else 'skyblue' for nm in self.my_node_names]
		nx.draw(self, self.my_pos, ax, node_color=color_map, node_size=3000, arrows=True)
		nx.draw_networkx_labels(self, self.my_pos, None, font_color="red")
		# nx.draw_networkx_edge_labels(fsm, self.my_pos, ax=ax, font_size=12)
		ax.axis('off')
		fig.tight_layout()
		canvas.draw()


# Tkinter app
root = tk.Tk()
root.title("FSM Visualizer")

# Create plot and embed it
fig, ax = plt.subplots(figsize=[13, 8]);

fsm = FSM()
#Wrong state (not always an error depends on last token)
fsm.new_node("ST_WRNG")
#Starting state
fsm.new_node("ST_STRT")
#Word state
fsm.new_node("ST_WORD")
#Operator state
fsm.new_node("ST_OPRA")
#Sequence state
fsm.new_node("ST_SEQ")
#Left subshell `(`
fsm.new_node("ST_LSSH")
#Right subshell `)`
fsm.new_node("ST_RSSH")
#Heredoc state
fsm.new_node("ST_HDOC")
#Redirect state
fsm.new_node("ST_REDR")
#Continue State
fsm.new_node("ST_CONT")
#End state
fsm.new_node("ST_END")
#Count of states 
fsm.new_node("STATE_COUN")

fsm.new_edge("ST_STRT", "ST_LSSH")
fsm.new_edge("ST_STRT", "ST_REDR")
fsm.new_edge("ST_STRT", "ST_HDOC")
fsm.new_edge("ST_STRT", "ST_WORD")
fsm.new_edge("ST_WORD", "ST_OPRA")
fsm.new_edge("ST_WORD", "ST_SEQ")
fsm.new_edge("ST_WORD", "ST_END")
fsm.new_edge("ST_WORD", "ST_WORD")
fsm.new_edge("ST_WORD", "ST_REDR")
fsm.new_edge("ST_WORD", "ST_RSSH")
fsm.new_edge("ST_WORD", "ST_HDOC")
fsm.new_edge("ST_WORD", "ST_WORD")
fsm.new_edge("ST_REDR", "ST_WORD")
fsm.new_edge("ST_HDOC", "ST_WORD")
fsm.new_edge("ST_OPRA", "ST_REDR")
fsm.new_edge("ST_OPRA", "ST_LSSH")
fsm.new_edge("ST_OPRA", "ST_WORD")
fsm.new_edge("ST_OPRA", "ST_CONT")
fsm.new_edge("ST_OPRA", "ST_HDOC")
fsm.new_edge("ST_CONT", "ST_STRT")
fsm.new_edge("ST_LSSH", "ST_WORD")
fsm.new_edge("ST_LSSH", "ST_REDR")
fsm.new_edge("ST_LSSH", "ST_HDOC")
fsm.new_edge("ST_LSSH", "ST_LSSH")
fsm.new_edge("ST_LSSH", "ST_END")
fsm.new_edge("ST_RSSH", "ST_END")
fsm.new_edge("ST_RSSH", "ST_RSSH")
fsm.new_edge("ST_RSSH", "ST_OPRA")
fsm.new_edge("ST_RSSH", "ST_SEQ")
fsm.new_edge("ST_RSSH", "ST_REDR")
fsm.new_edge("ST_RSSH", "ST_HDOC")
fsm.new_edge("ST_RSSH", "ST_WORD")
fsm.new_edge("ST_SEQ", "ST_END")
fsm.new_edge("ST_SEQ", "ST_WORD")
fsm.new_edge("ST_SEQ", "ST_REDR")
fsm.new_edge("ST_SEQ", "ST_HDOC")
fsm.new_edge("ST_SEQ", "ST_RSSH")
fsm.new_edge("ST_SEQ", "ST_LSSH")
fsm.new_edge("ST_END", "ST_STRT")
fsm.create_vis(fig, ax)
# print(fsm.my_noENDde_names)
canvas = FigureCanvasTkAgg(fig, master=root)
fsm.highlight_state("ST_END", fig, ax, canvas)
canvas.get_tk_widget().pack(fill=tk.BOTH, expand=True)
root.after(1000, lambda *a, **b: fsm.highlight_state("ST_STRT", fig, ax, canvas))

# Run the Tkinter event loop
root.mainloop()
exit()
