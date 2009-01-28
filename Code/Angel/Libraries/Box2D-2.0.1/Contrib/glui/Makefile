all:	libglui.a

CXXFLAGS=	-g -O2 -I../freeglut -L../freeglut -DGLUI_FREEGLUT

OBJECTS=	\
	algebra3.o \
	arcball.o \
	glui_add_controls.o \
	glui_bitmap_img_data.o \
	glui_bitmaps.o \
	glui_button.o \
	glui_checkbox.o \
	glui_column.o \
	glui_commandline.o \
	glui_control.o \
	glui.o \
	glui_edittext.o \
	glui_filebrowser.o \
	glui_listbox.o \
	glui_list.o \
	glui_mouse_iaction.o \
	glui_node.o \
	glui_panel.o \
	glui_radio.o \
	glui_rollout.o \
	glui_rotation.o \
	glui_scrollbar.o \
	glui_separator.o \
	glui_spinner.o \
	glui_statictext.o \
	glui_string.o \
	glui_textbox.o \
	glui_translation.o \
	glui_tree.o \
	glui_treepanel.o \
	glui_window.o \
	quaternion.o


libglui.a:	$(OBJECTS)
	ar cr libglui.a $(OBJECTS)

clean:
	rm -f $(OBJECTS) libglui.a

