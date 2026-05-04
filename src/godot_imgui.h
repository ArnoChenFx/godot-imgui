#ifndef IMGUI_GODOT_H
#define IMGUI_GODOT_H

#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/variant/rid.hpp>
#include <godot_cpp/classes/image.hpp>
#include <godot_cpp/classes/image_texture.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/input_event_key.hpp>
#include <godot_cpp/classes/input_event_mouse_button.hpp>
#include <godot_cpp/classes/input_event_mouse_motion.hpp>
#include <godot_cpp/classes/rendering_server.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include <../imgui/imgui.h>
#include <../imgui/imgui_internal.h>
#include <../imgui-node-editor/imgui_node_editor.h>

namespace godot {

class ImGuiGodot : public Control {
	GDCLASS(ImGuiGodot, Control)

private:
	bool initialized;
	bool enabled;
	bool use_dockspace;
	ImGuiID dock_space_id;
	ImGuiContext *imgui_context;
	double time;

	// Rendering
	RID canvas_item;
	Ref<ImageTexture> font_texture;
	Vector<RID> child_canvas_items;

	// Font configuration
	float font_size;
	String chinese_font_path;

	// Input state
	Vector2 mouse_pos;
	bool mouse_buttons[5];

	void setup_imgui_style();
	void create_fonts_texture();
	void render_draw_data();
	void update_mouse_cursor();
	void frame();

protected:
	static void _bind_methods();

public:
	ImGuiGodot();
	~ImGuiGodot();

	void _ready() override;
	void _process(double delta) override;
	void _input(const Ref<InputEvent> &event) override;
	void _notification(int p_what);

	// Enable/disable
	void set_enabled(bool p_enabled);
	bool is_enabled() const;

	// Dockspace
	void set_use_dockspace(bool p_use);
	bool is_use_dockspace() const;

	// Demo, Debug, Information
	void show_demo_window(bool show = true);
	void show_metrics_window(bool show = true);
	void show_about_window(bool show = true);
	void show_style_editor();

	// Window functions
	bool begin(const String &name, bool has_close_button = false, int window_flags = 0);
	void end();
	bool begin_child(const String &str_id, const Vector2 &size = Vector2(0, 0), int child_flags = 0, int window_flags = 0);
	void end_child();

	// Widgets: Text
	void text(const String &text);
	void text_colored(const Color &color, const String &text);
	void text_disabled(const String &text);
	void text_wrapped(const String &text);
	void label_text(const String &label, const String &text);
	void bullet_text(const String &text);

	// Widgets: Main
	bool button(const String &label, const Vector2 &size = Vector2(0, 0));
	bool small_button(const String &label);
	bool checkbox(const String &label, bool value);
	bool radio_button(const String &label, bool active);

	// Widgets: Sliders
	float slider_float(const String &label, float value, float min_value, float max_value);
	int slider_int(const String &label, int value, int min_value, int max_value);

	// Widgets: Input
	String input_text(const String &label, const String &text, int max_length = 256);
	float input_float(const String &label, float value);
	int input_int(const String &label, int value);

	// Widgets: Trees
	bool tree_node(const String &label);
	void tree_pop();

	// Widgets: Selectables
	bool selectable(const String &label, bool selected = false);

	// Widgets: Combo boxes
	bool begin_combo(const String &label, const String &preview_value, int flags = 0);
	void end_combo();
	int combo(const String &label, int current_item, const PackedStringArray &items, int popup_max_height_in_items = -1);

	// Widgets: Drag
	float drag_float(const String &label, float value, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f);
	int drag_int(const String &label, int value, float v_speed = 1.0f, int v_min = 0, int v_max = 0);
	Vector2 drag_float2(const String &label, const Vector2 &value, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f);
	Vector3 drag_float3(const String &label, const Vector3 &value, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f);

	// Widgets: Multi-component sliders
	Vector2 slider_float2(const String &label, const Vector2 &value, float v_min, float v_max);
	Vector3 slider_float3(const String &label, const Vector3 &value, float v_min, float v_max);

	// Widgets: Color pickers
	Color color_edit3(const String &label, const Color &color, int flags = 0);
	Color color_edit4(const String &label, const Color &color, int flags = 0);
	Color color_picker3(const String &label, const Color &color, int flags = 0);
	Color color_picker4(const String &label, const Color &color, int flags = 0);
	bool color_button(const String &desc_id, const Color &color, int flags = 0, const Vector2 &size = Vector2(0, 0));

	// Widgets: Misc
	bool collapsing_header(const String &label, int flags = 0);
	void progress_bar(float fraction, const Vector2 &size = Vector2(-1, 0), const String &overlay = "");
	void bullet();

	// Menus
	bool begin_main_menu_bar();
	void end_main_menu_bar();
	bool begin_menu_bar();
	void end_menu_bar();
	bool begin_menu(const String &label, bool enabled = true);
	void end_menu();
	bool menu_item(const String &label, const String &shortcut = "", bool selected = false, bool enabled = true);

	// Popups
	void open_popup(const String &str_id, int popup_flags = 0);
	bool begin_popup(const String &str_id, int window_flags = 0);
	bool begin_popup_modal(const String &name, bool has_close_button = false, int window_flags = 0);
	void end_popup();
	void close_current_popup();

	// Tooltips
	bool begin_tooltip();
	void end_tooltip();
	void set_tooltip(const String &text);

	// Tables
	bool begin_table(const String &str_id, int columns, int flags = 0, const Vector2 &outer_size = Vector2(0, 0), float inner_width = 0.0f);
	void end_table();
	void table_next_row(int row_flags = 0, float min_row_height = 0.0f);
	bool table_next_column();
	bool table_set_column_index(int column_n);
	void table_setup_column(const String &label, int flags = 0, float init_width_or_weight = 0.0f, int user_id = 0);
	void table_headers_row();

	// Tab bars
	bool begin_tab_bar(const String &str_id, int flags = 0);
	void end_tab_bar();
	bool begin_tab_item(const String &label, bool has_close_button = false, int flags = 0);
	void end_tab_item();

	// Layout
	void separator();
	void separator_text(const String &label);
	void same_line(float offset_from_start_x = 0.0f, float spacing = -1.0f);
	void new_line();
	void spacing();
	void dummy(const Vector2 &size);
	void indent(float indent_w = 0.0f);
	void unindent(float indent_w = 0.0f);
	void begin_group();
	void end_group();
	Vector2 get_content_region_avail();
	Vector2 get_cursor_screen_pos();
	void set_cursor_screen_pos(const Vector2 &pos);

	// Cursor / Layout
	Vector2 get_cursor_pos();
	void set_cursor_pos(const Vector2 &pos);
	float get_cursor_pos_x();
	float get_cursor_pos_y();
	void set_cursor_pos_x(float x);
	void set_cursor_pos_y(float y);

	// ID stack
	void push_id(const String &id);
	void pop_id();

	// Style
	void push_style_color(int idx, const Color &color);
	void pop_style_color(int count = 1);
	void push_style_var_float(int idx, float val);
	void push_style_var_vec2(int idx, const Vector2 &val);
	void pop_style_var(int count = 1);

	// Item/Widget utilities
	bool is_item_hovered(int flags = 0);
	bool is_item_active();
	bool is_item_focused();
	bool is_item_clicked(int mouse_button = 0);
	bool is_item_visible();
	bool is_item_edited();
	bool is_item_activated();
	bool is_item_deactivated();
	bool is_item_deactivated_after_edit();
	Vector2 get_item_rect_min();
	Vector2 get_item_rect_max();
	Vector2 get_item_rect_size();

	// Window utilities
	bool is_window_appearing();
	bool is_window_collapsed();
	bool is_window_focused(int flags = 0);
	bool is_window_hovered(int flags = 0);
	Vector2 get_window_pos();
	Vector2 get_window_size();
	float get_window_width();
	float get_window_height();

	// Miscellaneous utilities
	bool is_mouse_down(int button);
	bool is_mouse_clicked(int button, bool repeat = false);
	bool is_mouse_double_clicked(int button);
	Vector2 get_mouse_pos();
	void set_next_window_pos(const Vector2 &pos, int cond = 0, const Vector2 &pivot = Vector2(0, 0));
	void set_next_window_size(const Vector2 &size, int cond = 0);
	void set_next_window_collapsed(bool collapsed, int cond = 0);
	void set_next_window_focus();
	void set_next_window_dock_id(int dock_id, int cond = 0);

	// Docking
	int get_dock_space_id() const;
	int get_main_viewport_id() const;
	int dock_space(int id, const Vector2 &size, int flags);
	int dock_builder_add_node(int node_id, int flags);
	void dock_builder_remove_node(int node_id);
	void dock_builder_set_node_pos(int node_id, const Vector2 &pos);
	void dock_builder_set_node_size(int node_id, const Vector2 &size);
	Array dock_builder_split_node(int node_id, int split_dir, float ratio);
	void dock_builder_dock_window(const String &window_name, int node_id);
	void dock_builder_finish(int node_id);
	int dock_builder_get_central_node(int node_id);

	// Node Editor - Lifecycle
	int64_t node_editor_create_editor();
	void node_editor_destroy_editor(int64_t editor_context);
	void node_editor_set_current_editor(int64_t editor_context);

	// Node Editor - Frame
	void node_editor_begin(const String &id, const Vector2 &size = Vector2(0, 0));
	void node_editor_end();

	// Node Editor - Nodes
	void node_editor_begin_node(int64_t id);
	void node_editor_end_node();
	void node_editor_set_node_position(int64_t id, const Vector2 &pos);
	Vector2 node_editor_get_node_position(int64_t id);
	Vector2 node_editor_get_node_size(int64_t id);
	void node_editor_center_node_on_screen(int64_t id);

	// Node Editor - Pins
	void node_editor_begin_pin(int64_t id, int kind);
	void node_editor_end_pin();
	void node_editor_pin_rect(const Vector2 &a, const Vector2 &b);
	void node_editor_pin_pivot_rect(const Vector2 &a, const Vector2 &b);
	void node_editor_pin_pivot_alignment(const Vector2 &alignment);

	// Node Editor - Links
	bool node_editor_link(int64_t id, int64_t start_pin_id, int64_t end_pin_id, const Color &color = Color(1, 1, 1, 1), float thickness = 1.0f);
	bool node_editor_delete_link(int64_t id);
	void node_editor_flow(int64_t link_id, int direction = 0);

	// Node Editor - Create Interaction
	bool node_editor_begin_create(const Color &color = Color(1, 1, 1, 1), float thickness = 1.0f);
	void node_editor_end_create();
	Array node_editor_query_new_link();
	Array node_editor_query_new_node();
	bool node_editor_accept_new_item();
	void node_editor_reject_new_item();

	// Node Editor - Delete Interaction
	bool node_editor_begin_delete();
	void node_editor_end_delete();
	Array node_editor_query_deleted_link();
	Array node_editor_query_deleted_node();
	bool node_editor_accept_deleted_item();
	void node_editor_reject_deleted_item();

	// Node Editor - Selection
	int node_editor_get_selected_node_count();
	PackedInt64Array node_editor_get_selected_nodes(int max_count = 256);
	bool node_editor_is_node_selected(int64_t id);
	void node_editor_select_node(int64_t id, bool append = false);
	void node_editor_clear_selection();

	// Node Editor - Hover / Click
	int64_t node_editor_get_hovered_node();
	int64_t node_editor_get_hovered_pin();
	int64_t node_editor_get_hovered_link();
	int64_t node_editor_get_double_clicked_node();
	bool node_editor_show_background_context_menu();
	Array node_editor_show_node_context_menu();

	// Node Editor - Navigation
	void node_editor_navigate_to_content(float duration = -1.0f);
	void node_editor_navigate_to_selection(bool zoom_in = false, float duration = -1.0f);
	float node_editor_get_current_zoom();

	// Node Editor - Style
	void node_editor_push_style_color(int idx, const Color &color);
	void node_editor_pop_style_color(int count = 1);
	void node_editor_push_style_var_float(int idx, float val);
	void node_editor_push_style_var_vec2(int idx, const Vector2 &val);
	void node_editor_pop_style_var(int count = 1);

	// Node Editor - Utility
	void node_editor_suspend();
	void node_editor_resume();
	Vector2 node_editor_screen_to_canvas(const Vector2 &pos);
	Vector2 node_editor_canvas_to_screen(const Vector2 &pos);

	// Font configuration
	void set_chinese_font_path(const String &path);
	void set_font_size(float size);

	// Internal - not exposed to GDScript
	ImGuiContext *get_context_internal() { return imgui_context; }
};

} // namespace godot

#endif // IMGUI_GODOT_H
