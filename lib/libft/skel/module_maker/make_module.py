from tkinter import Tk, filedialog, messagebox, simpledialog
import os
import subprocess
import sys
import jinja2 as j2

modules = []

def populate_modules():
	global modules
	modules = []
	# for each folder in current directory that is not .git or .vscode or __pycache__ or skel
	for item in os.listdir("."):
		if os.path.isdir(item) and item not in [".git", ".vscode", "__pycache__", "skel"]:
			modules.append(item)

class ModuleMaker:
	instance = None
	def __new__(cls):
		if cls.instance is None:
			cls.instance = super().__new__(cls)
		return cls.instance

	def __init__(self):
		self.root = Tk()
		self.root.withdraw()
		self.module_name = ""
		self.module_dir = ""
		self.dependencies = []
		self.files = ["Makefile"]
		self.template_loader = j2.FileSystemLoader(searchpath="./skel")
		self.template_env = j2.Environment(loader=self.template_loader)
		populate_modules()  # Populate the modules list
		self.get_module_name()

	def get_module_name(self):
		self.module_name = ""
		while (not self.module_name) \
			or (self.module_name in modules) \
			or (not self.module_name.isidentifier()):
			popup = simpledialog.askstring("Module Name",
						"Enter the module name (e.g., my_module):")
			if popup is None:
				self.root.quit()
				self.root.destroy()
				return
			self.module_name = popup.strip()
		self.files += [f"ft_{self.module_name}.h"]
		self.show_window()

	def show_window(self):
		self.window = Tk()
		self.window.title(f"Module: {self.module_name}")
		self.window.geometry("400x300")
		self.init_ui()
		self.window.mainloop()
	
	def init_ui(self):
		global modules
		# so I want this to be like a wizard style thing,
		# the info we need to collect is: 
		# - module name (done) (module name will directly be the folder name)
		# - module directory (done)
		# - files to create, we will need to add the header
		# - checkboxes for any required submodules
		# - confirm and create module
		from tkinter import Label, Button, Checkbutton, IntVar, Frame, Entry, StringVar, Scrollbar, Listbox, MULTIPLE, END, Text
		self.module_dir = self.module_dir.replace(" ", "_")
		Label(self.window, text="Select Dependencies: ").pack()
		self.dep_select = Listbox(self.window, selectmode=MULTIPLE, exportselection=0, height=6)
		# Populate the listbox with modules
		for module in modules:
			self.dep_select.insert(END, module)
		self.dep_select.bind('<<ListboxSelect>>', lambda e: self.update_dependencies())
		self.dep_select.pack()
		Label(self.window, text="Additional Files (one per line): ").pack()
		self.file_entry = Text(self.window, height=4, width=40)
		self.file_entry.pack()
		Button(self.window, text="Create Module", command=self.create_module).pack(pady=10)

	def update_dependencies(self):
		selected_indices = self.dep_select.curselection()
		self.dependencies = [modules[i] for i in selected_indices]

	def generate_files(self):
		for filename in self.files:
			with open(self.module_dir + "/" + filename, "w") as f:
				pass

	def update_makefile(self):
		template = self.template_env.get_template("Makefile.skel")

		# need to add all the components of the module from here
		template.globals['deps'] = self.dependencies
		template.globals['files'] = self.files
		template.globals['module_name'] = self.module_name

		output = template.render(module_name=self.module_name, dependencies=self.dependencies)
		with open(self.module_dir + "/Makefile", "w") as f:
			f.write(output)

	def update_header(self):
		template = self.template_env.get_template("header.skel")

		# need to add all the components of the module from here
		template.globals['deps'] = self.dependencies
		template.globals['module_name'] = self.module_name

		output = template.render(module_name=self.module_name, dependencies=self.dependencies)
		header_filename = f"{self.module_dir}/ft_{self.module_name}.h"
		with open(header_filename, "w") as f:
			f.write(output)
		return
	
	def link_back(self):
		print("Linking back to libft.h")
		# need to link the header back to libft.h
		libft_header = "./include/libft.h"
		if not os.path.exists(libft_header):
			messagebox.showwarning("Warning", f"Could not find {libft_header} to link back the new module header.")
			return
		with open(libft_header, "r") as f:
			lines = f.readlines()
		main_line = f"#  define FT_INCLUDE_{self.module_name.upper()}\n"
		include_lines = f"# ifdef FT_INCLUDE_{self.module_name.upper()}\n#  include \"ft_{self.module_name}.h\"\n# endif\n\n"
		modified_lines = []
		for line in lines:
			if (line.strip() == "/*include here*/"):
				modified_lines.append(include_lines)
			elif (line.strip() == "/*define all*/"):
				modified_lines.append(main_line)
			modified_lines.append(line)
		with open(libft_header, "w") as f:
			f.writelines(modified_lines)
		# Create symlink in include directory
		symlink_target = f"../{self.module_dir}/ft_{self.module_name}.h"
		symlink_path = f"./include/ft_{self.module_name}.h"
		os.system(f"ln -sf {symlink_target} {symlink_path}")
		print(f"Successfully linked ft_{self.module_name}.h to libft.h")

	def create_module(self):
		additional_files = self.file_entry.get("1.0", "end-1c").strip()
		if additional_files:
			for f in additional_files.split("\n"):
				f = f.strip()
				if f and f not in self.files:
					self.files.append(f)
		self.module_dir = self.module_name
		try:
			os.makedirs(self.module_dir, exist_ok=False)
		except FileExistsError:
			messagebox.showerror("Error", f"Module directory '{self.module_dir}' already exists.")
			return
		self.generate_files()
		self.update_makefile()
		self.update_header()
		self.link_back()
		messagebox.showinfo("Success", f"Module '{self.module_name}' created successfully.")
		self.window.destroy()
		self.root.destroy()

# assume we are running this from the skel/module_maker/ directory
if __name__ == "__main__":
	directory = subprocess.run(["git", "rev-parse", "--show-toplevel"], capture_output=True, text=True).stdout.strip()
	os.chdir(directory)
	app = ModuleMaker()