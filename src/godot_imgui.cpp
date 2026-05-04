#include "godot_imgui.h"

#include <godot_cpp/classes/display_server.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/image.hpp>
#include <godot_cpp/classes/image_texture.hpp>
#include <godot_cpp/classes/rendering_server.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/viewport.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "fonts/Simhei.cpp"
#include "fonts/Roboto_Medium.cpp"

using namespace godot;

void ImGuiGodot::_bind_methods() {
	// Signal emitted between NewFrame and Render, for multi-script ImGui drawing
	ADD_SIGNAL(MethodInfo("on_imgui_frame"));

	// Demo, Debug, Information
	ClassDB::bind_method(D_METHOD("show_demo_window", "show"), &ImGuiGodot::show_demo_window, DEFVAL(true));
	ClassDB::bind_method(D_METHOD("show_metrics_window", "show"), &ImGuiGodot::show_metrics_window, DEFVAL(true));
	ClassDB::bind_method(D_METHOD("show_about_window", "show"), &ImGuiGodot::show_about_window, DEFVAL(true));
	ClassDB::bind_method(D_METHOD("show_style_editor"), &ImGuiGodot::show_style_editor);

	// Window functions
	ClassDB::bind_method(D_METHOD("begin", "name", "has_close_button"), &ImGuiGodot::begin, DEFVAL(false));
	ClassDB::bind_method(D_METHOD("end"), &ImGuiGodot::end);
	ClassDB::bind_method(D_METHOD("begin_child", "str_id", "size", "child_flags", "window_flags"), &ImGuiGodot::begin_child, DEFVAL(Vector2(0, 0)), DEFVAL(0), DEFVAL(0));
	ClassDB::bind_method(D_METHOD("end_child"), &ImGuiGodot::end_child);

	// Widgets: Text
	ClassDB::bind_method(D_METHOD("text", "text"), &ImGuiGodot::text);
	ClassDB::bind_method(D_METHOD("text_colored", "color", "text"), &ImGuiGodot::text_colored);
	ClassDB::bind_method(D_METHOD("text_disabled", "text"), &ImGuiGodot::text_disabled);
	ClassDB::bind_method(D_METHOD("text_wrapped", "text"), &ImGuiGodot::text_wrapped);
	ClassDB::bind_method(D_METHOD("label_text", "label", "text"), &ImGuiGodot::label_text);
	ClassDB::bind_method(D_METHOD("bullet_text", "text"), &ImGuiGodot::bullet_text);

	// Widgets: Main
	ClassDB::bind_method(D_METHOD("button", "label", "size"), &ImGuiGodot::button, DEFVAL(Vector2(0, 0)));
	ClassDB::bind_method(D_METHOD("small_button", "label"), &ImGuiGodot::small_button);
	ClassDB::bind_method(D_METHOD("checkbox", "label", "value"), &ImGuiGodot::checkbox);
	ClassDB::bind_method(D_METHOD("radio_button", "label", "active"), &ImGuiGodot::radio_button);

	// Widgets: Sliders
	ClassDB::bind_method(D_METHOD("slider_float", "label", "value", "min_value", "max_value"), &ImGuiGodot::slider_float);
	ClassDB::bind_method(D_METHOD("slider_int", "label", "value", "min_value", "max_value"), &ImGuiGodot::slider_int);

	// Widgets: Input
	ClassDB::bind_method(D_METHOD("input_text", "label", "text", "max_length"), &ImGuiGodot::input_text, DEFVAL(256));
	ClassDB::bind_method(D_METHOD("input_float", "label", "value"), &ImGuiGodot::input_float);
	ClassDB::bind_method(D_METHOD("input_int", "label", "value"), &ImGuiGodot::input_int);

	// Widgets: Trees
	ClassDB::bind_method(D_METHOD("tree_node", "label"), &ImGuiGodot::tree_node);
	ClassDB::bind_method(D_METHOD("tree_pop"), &ImGuiGodot::tree_pop);

	// Widgets: Selectables
	ClassDB::bind_method(D_METHOD("selectable", "label", "selected"), &ImGuiGodot::selectable, DEFVAL(false));

	// Widgets: Combo boxes
	ClassDB::bind_method(D_METHOD("begin_combo", "label", "preview_value", "flags"), &ImGuiGodot::begin_combo, DEFVAL(0));
	ClassDB::bind_method(D_METHOD("end_combo"), &ImGuiGodot::end_combo);
	ClassDB::bind_method(D_METHOD("combo", "label", "current_item", "items", "popup_max_height_in_items"), &ImGuiGodot::combo, DEFVAL(-1));

	// Widgets: Drag
	ClassDB::bind_method(D_METHOD("drag_float", "label", "value", "v_speed", "v_min", "v_max"), &ImGuiGodot::drag_float, DEFVAL(1.0f), DEFVAL(0.0f), DEFVAL(0.0f));
	ClassDB::bind_method(D_METHOD("drag_int", "label", "value", "v_speed", "v_min", "v_max"), &ImGuiGodot::drag_int, DEFVAL(1.0f), DEFVAL(0), DEFVAL(0));
	ClassDB::bind_method(D_METHOD("drag_float2", "label", "value", "v_speed", "v_min", "v_max"), &ImGuiGodot::drag_float2, DEFVAL(1.0f), DEFVAL(0.0f), DEFVAL(0.0f));
	ClassDB::bind_method(D_METHOD("drag_float3", "label", "value", "v_speed", "v_min", "v_max"), &ImGuiGodot::drag_float3, DEFVAL(1.0f), DEFVAL(0.0f), DEFVAL(0.0f));

	// Widgets: Multi-component sliders
	ClassDB::bind_method(D_METHOD("slider_float2", "label", "value", "v_min", "v_max"), &ImGuiGodot::slider_float2);
	ClassDB::bind_method(D_METHOD("slider_float3", "label", "value", "v_min", "v_max"), &ImGuiGodot::slider_float3);

	// Widgets: Color pickers
	ClassDB::bind_method(D_METHOD("color_edit3", "label", "color", "flags"), &ImGuiGodot::color_edit3, DEFVAL(0));
	ClassDB::bind_method(D_METHOD("color_edit4", "label", "color", "flags"), &ImGuiGodot::color_edit4, DEFVAL(0));
	ClassDB::bind_method(D_METHOD("color_picker3", "label", "color", "flags"), &ImGuiGodot::color_picker3, DEFVAL(0));
	ClassDB::bind_method(D_METHOD("color_picker4", "label", "color", "flags"), &ImGuiGodot::color_picker4, DEFVAL(0));
	ClassDB::bind_method(D_METHOD("color_button", "desc_id", "color", "flags", "size"), &ImGuiGodot::color_button, DEFVAL(0), DEFVAL(Vector2(0, 0)));

	// Widgets: Misc
	ClassDB::bind_method(D_METHOD("collapsing_header", "label", "flags"), &ImGuiGodot::collapsing_header, DEFVAL(0));
	ClassDB::bind_method(D_METHOD("progress_bar", "fraction", "size", "overlay"), &ImGuiGodot::progress_bar, DEFVAL(Vector2(-1, 0)), DEFVAL(""));
	ClassDB::bind_method(D_METHOD("bullet"), &ImGuiGodot::bullet);

	// Menus
	ClassDB::bind_method(D_METHOD("begin_main_menu_bar"), &ImGuiGodot::begin_main_menu_bar);
	ClassDB::bind_method(D_METHOD("end_main_menu_bar"), &ImGuiGodot::end_main_menu_bar);
	ClassDB::bind_method(D_METHOD("begin_menu_bar"), &ImGuiGodot::begin_menu_bar);
	ClassDB::bind_method(D_METHOD("end_menu_bar"), &ImGuiGodot::end_menu_bar);
	ClassDB::bind_method(D_METHOD("begin_menu", "label", "enabled"), &ImGuiGodot::begin_menu, DEFVAL(true));
	ClassDB::bind_method(D_METHOD("end_menu"), &ImGuiGodot::end_menu);
	ClassDB::bind_method(D_METHOD("menu_item", "label", "shortcut", "selected", "enabled"), &ImGuiGodot::menu_item, DEFVAL(""), DEFVAL(false), DEFVAL(true));

	// Popups
	ClassDB::bind_method(D_METHOD("open_popup", "str_id", "popup_flags"), &ImGuiGodot::open_popup, DEFVAL(0));
	ClassDB::bind_method(D_METHOD("begin_popup", "str_id", "window_flags"), &ImGuiGodot::begin_popup, DEFVAL(0));
	ClassDB::bind_method(D_METHOD("begin_popup_modal", "name", "has_close_button", "window_flags"), &ImGuiGodot::begin_popup_modal, DEFVAL(false), DEFVAL(0));
	ClassDB::bind_method(D_METHOD("end_popup"), &ImGuiGodot::end_popup);
	ClassDB::bind_method(D_METHOD("close_current_popup"), &ImGuiGodot::close_current_popup);

	// Tooltips
	ClassDB::bind_method(D_METHOD("begin_tooltip"), &ImGuiGodot::begin_tooltip);
	ClassDB::bind_method(D_METHOD("end_tooltip"), &ImGuiGodot::end_tooltip);
	ClassDB::bind_method(D_METHOD("set_tooltip", "text"), &ImGuiGodot::set_tooltip);

	// Tables
	ClassDB::bind_method(D_METHOD("begin_table", "str_id", "columns", "flags", "outer_size", "inner_width"), &ImGuiGodot::begin_table, DEFVAL(0), DEFVAL(Vector2(0, 0)), DEFVAL(0.0f));
	ClassDB::bind_method(D_METHOD("end_table"), &ImGuiGodot::end_table);
	ClassDB::bind_method(D_METHOD("table_next_row", "row_flags", "min_row_height"), &ImGuiGodot::table_next_row, DEFVAL(0), DEFVAL(0.0f));
	ClassDB::bind_method(D_METHOD("table_next_column"), &ImGuiGodot::table_next_column);
	ClassDB::bind_method(D_METHOD("table_set_column_index", "column_n"), &ImGuiGodot::table_set_column_index);
	ClassDB::bind_method(D_METHOD("table_setup_column", "label", "flags", "init_width_or_weight", "user_id"), &ImGuiGodot::table_setup_column, DEFVAL(0), DEFVAL(0.0f), DEFVAL(0));
	ClassDB::bind_method(D_METHOD("table_headers_row"), &ImGuiGodot::table_headers_row);

	// Tab bars
	ClassDB::bind_method(D_METHOD("begin_tab_bar", "str_id", "flags"), &ImGuiGodot::begin_tab_bar, DEFVAL(0));
	ClassDB::bind_method(D_METHOD("end_tab_bar"), &ImGuiGodot::end_tab_bar);
	ClassDB::bind_method(D_METHOD("begin_tab_item", "label", "has_close_button", "flags"), &ImGuiGodot::begin_tab_item, DEFVAL(false), DEFVAL(0));
	ClassDB::bind_method(D_METHOD("end_tab_item"), &ImGuiGodot::end_tab_item);

	// Layout
	ClassDB::bind_method(D_METHOD("separator"), &ImGuiGodot::separator);
	ClassDB::bind_method(D_METHOD("separator_text", "label"), &ImGuiGodot::separator_text);
	ClassDB::bind_method(D_METHOD("same_line", "offset_from_start_x", "spacing"), &ImGuiGodot::same_line, DEFVAL(0.0f), DEFVAL(-1.0f));
	ClassDB::bind_method(D_METHOD("new_line"), &ImGuiGodot::new_line);
	ClassDB::bind_method(D_METHOD("spacing"), &ImGuiGodot::spacing);
	ClassDB::bind_method(D_METHOD("dummy", "size"), &ImGuiGodot::dummy);
	ClassDB::bind_method(D_METHOD("indent", "indent_w"), &ImGuiGodot::indent, DEFVAL(0.0f));
	ClassDB::bind_method(D_METHOD("unindent", "indent_w"), &ImGuiGodot::unindent, DEFVAL(0.0f));
	ClassDB::bind_method(D_METHOD("begin_group"), &ImGuiGodot::begin_group);
	ClassDB::bind_method(D_METHOD("end_group"), &ImGuiGodot::end_group);
	ClassDB::bind_method(D_METHOD("get_content_region_avail"), &ImGuiGodot::get_content_region_avail);
	ClassDB::bind_method(D_METHOD("get_cursor_screen_pos"), &ImGuiGodot::get_cursor_screen_pos);
	ClassDB::bind_method(D_METHOD("set_cursor_screen_pos", "pos"), &ImGuiGodot::set_cursor_screen_pos);

	// Cursor / Layout
	ClassDB::bind_method(D_METHOD("get_cursor_pos"), &ImGuiGodot::get_cursor_pos);
	ClassDB::bind_method(D_METHOD("set_cursor_pos", "pos"), &ImGuiGodot::set_cursor_pos);
	ClassDB::bind_method(D_METHOD("get_cursor_pos_x"), &ImGuiGodot::get_cursor_pos_x);
	ClassDB::bind_method(D_METHOD("get_cursor_pos_y"), &ImGuiGodot::get_cursor_pos_y);
	ClassDB::bind_method(D_METHOD("set_cursor_pos_x", "x"), &ImGuiGodot::set_cursor_pos_x);
	ClassDB::bind_method(D_METHOD("set_cursor_pos_y", "y"), &ImGuiGodot::set_cursor_pos_y);

	// ID stack
	ClassDB::bind_method(D_METHOD("push_id", "id"), &ImGuiGodot::push_id);
	ClassDB::bind_method(D_METHOD("pop_id"), &ImGuiGodot::pop_id);

	// Style
	ClassDB::bind_method(D_METHOD("push_style_color", "idx", "color"), &ImGuiGodot::push_style_color);
	ClassDB::bind_method(D_METHOD("pop_style_color", "count"), &ImGuiGodot::pop_style_color, DEFVAL(1));
	ClassDB::bind_method(D_METHOD("push_style_var_float", "idx", "val"), &ImGuiGodot::push_style_var_float);
	ClassDB::bind_method(D_METHOD("push_style_var_vec2", "idx", "val"), &ImGuiGodot::push_style_var_vec2);
	ClassDB::bind_method(D_METHOD("pop_style_var", "count"), &ImGuiGodot::pop_style_var, DEFVAL(1));

	// Item/Widget utilities
	ClassDB::bind_method(D_METHOD("is_item_hovered", "flags"), &ImGuiGodot::is_item_hovered, DEFVAL(0));
	ClassDB::bind_method(D_METHOD("is_item_active"), &ImGuiGodot::is_item_active);
	ClassDB::bind_method(D_METHOD("is_item_focused"), &ImGuiGodot::is_item_focused);
	ClassDB::bind_method(D_METHOD("is_item_clicked", "mouse_button"), &ImGuiGodot::is_item_clicked, DEFVAL(0));
	ClassDB::bind_method(D_METHOD("is_item_visible"), &ImGuiGodot::is_item_visible);
	ClassDB::bind_method(D_METHOD("is_item_edited"), &ImGuiGodot::is_item_edited);
	ClassDB::bind_method(D_METHOD("is_item_activated"), &ImGuiGodot::is_item_activated);
	ClassDB::bind_method(D_METHOD("is_item_deactivated"), &ImGuiGodot::is_item_deactivated);
	ClassDB::bind_method(D_METHOD("is_item_deactivated_after_edit"), &ImGuiGodot::is_item_deactivated_after_edit);
	ClassDB::bind_method(D_METHOD("get_item_rect_min"), &ImGuiGodot::get_item_rect_min);
	ClassDB::bind_method(D_METHOD("get_item_rect_max"), &ImGuiGodot::get_item_rect_max);
	ClassDB::bind_method(D_METHOD("get_item_rect_size"), &ImGuiGodot::get_item_rect_size);

	// Window utilities
	ClassDB::bind_method(D_METHOD("is_window_appearing"), &ImGuiGodot::is_window_appearing);
	ClassDB::bind_method(D_METHOD("is_window_collapsed"), &ImGuiGodot::is_window_collapsed);
	ClassDB::bind_method(D_METHOD("is_window_focused", "flags"), &ImGuiGodot::is_window_focused, DEFVAL(0));
	ClassDB::bind_method(D_METHOD("is_window_hovered", "flags"), &ImGuiGodot::is_window_hovered, DEFVAL(0));
	ClassDB::bind_method(D_METHOD("get_window_pos"), &ImGuiGodot::get_window_pos);
	ClassDB::bind_method(D_METHOD("get_window_size"), &ImGuiGodot::get_window_size);
	ClassDB::bind_method(D_METHOD("get_window_width"), &ImGuiGodot::get_window_width);
	ClassDB::bind_method(D_METHOD("get_window_height"), &ImGuiGodot::get_window_height);

	// Miscellaneous utilities
	ClassDB::bind_method(D_METHOD("is_mouse_down", "button"), &ImGuiGodot::is_mouse_down);
	ClassDB::bind_method(D_METHOD("is_mouse_clicked", "button", "repeat"), &ImGuiGodot::is_mouse_clicked, DEFVAL(false));
	ClassDB::bind_method(D_METHOD("is_mouse_double_clicked", "button"), &ImGuiGodot::is_mouse_double_clicked);
	ClassDB::bind_method(D_METHOD("get_mouse_pos"), &ImGuiGodot::get_mouse_pos);
	ClassDB::bind_method(D_METHOD("set_next_window_pos", "pos", "cond", "pivot"), &ImGuiGodot::set_next_window_pos, DEFVAL(0), DEFVAL(Vector2(0, 0)));
	ClassDB::bind_method(D_METHOD("set_next_window_size", "size", "cond"), &ImGuiGodot::set_next_window_size, DEFVAL(0));
	ClassDB::bind_method(D_METHOD("set_next_window_collapsed", "collapsed", "cond"), &ImGuiGodot::set_next_window_collapsed, DEFVAL(0));
	ClassDB::bind_method(D_METHOD("set_next_window_focus"), &ImGuiGodot::set_next_window_focus);

	// Enable/disable
	ClassDB::bind_method(D_METHOD("set_enabled", "enabled"), &ImGuiGodot::set_enabled);
	ClassDB::bind_method(D_METHOD("is_enabled"), &ImGuiGodot::is_enabled);

	// Font configuration
	ClassDB::bind_method(D_METHOD("set_chinese_font_path", "path"), &ImGuiGodot::set_chinese_font_path);
	ClassDB::bind_method(D_METHOD("set_font_size", "size"), &ImGuiGodot::set_font_size);
}

ImGuiGodot::ImGuiGodot() {
	initialized = false;
	enabled = true;
	imgui_context = nullptr;
	time = 0.0;
	mouse_pos = Vector2(0, 0);
	font_size = 14.0f;

	for (int i = 0; i < 5; i++) {
		mouse_buttons[i] = false;
	}
}

ImGuiGodot::~ImGuiGodot() {
	if (imgui_context) {
		ImGui::DestroyContext(imgui_context);
		imgui_context = nullptr;
	}
}

void ImGuiGodot::_ready() {
	// Create ImGui context
	imgui_context = ImGui::CreateContext();
	ImGui::SetCurrentContext(imgui_context);

	ImGuiIO &io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;   // 启用 Docking

	// Setup display size
	Viewport *viewport = get_viewport();
	if (viewport) {
		Rect2 rect = viewport->get_visible_rect();
		io.DisplaySize = ImVec2(rect.size.x, rect.size.y);
	}

	setup_imgui_style();
	create_fonts_texture();

	set_anchors_and_offsets_preset(Control::LayoutPreset::PRESET_FULL_RECT);

	UtilityFunctions::print("ImGui-Godot initialized");
	initialized = true;
}

void ImGuiGodot::_process(double delta) {
	if (!initialized || !enabled) {
		return;
	}

	time += delta;

	ImGuiIO &io = ImGui::GetIO();
	io.DeltaTime = (float)delta;

	// Update display size — viewport in runtime, control size in editor
	if (Engine::get_singleton()->is_editor_hint()) {
		Vector2 size = get_size();
		if (size.x > 0 && size.y > 0) {
			io.DisplaySize = ImVec2(size.x, size.y);
		}
	} else {
		Viewport *viewport = get_viewport();
		if (viewport) {
			Rect2 rect = viewport->get_visible_rect();
			io.DisplaySize = ImVec2(rect.size.x, rect.size.y);
		}
	}

	// Update mouse position
	io.MousePos = ImVec2(mouse_pos.x, mouse_pos.y);

	// Update mouse buttons
	for (int i = 0; i < 5; i++) {
		io.MouseDown[i] = mouse_buttons[i];
	}

	// Auto-manage frame lifecycle — scripts hook into on_imgui_frame signal
	ImGui::NewFrame();
	ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

	emit_signal("on_imgui_frame");

	ImGui::Render();
	queue_redraw();
}

void ImGuiGodot::_input(const Ref<InputEvent> &event) {
	if (!initialized || !enabled) {
		return;
	}

	ImGuiIO &io = ImGui::GetIO();

	// Mouse motion — adjust to control-local coordinates
	Ref<InputEventMouseMotion> mouse_motion = event;
	if (mouse_motion.is_valid()) {
		mouse_pos = mouse_motion->get_position() - get_global_position();
	}

	// Mouse buttons
	Ref<InputEventMouseButton> mouse_button = event;
	if (mouse_button.is_valid()) {
		int button_index = (int)mouse_button->get_button_index();
		if (button_index >= 1 && button_index <= 5) {
			mouse_buttons[button_index - 1] = mouse_button->is_pressed();
		}

		// Mouse wheel
		if (button_index == (int)MouseButton::MOUSE_BUTTON_WHEEL_UP) {
			io.MouseWheel += 1.0f;
		} else if (button_index == (int)MouseButton::MOUSE_BUTTON_WHEEL_DOWN) {
			io.MouseWheel -= 1.0f;
		}
	}

	// Keyboard
	Ref<InputEventKey> key_event = event;
	if (key_event.is_valid()) {
		// Update modifier keys
		io.AddKeyEvent(ImGuiMod_Ctrl, key_event->is_ctrl_pressed());
		io.AddKeyEvent(ImGuiMod_Shift, key_event->is_shift_pressed());
		io.AddKeyEvent(ImGuiMod_Alt, key_event->is_alt_pressed());
		io.AddKeyEvent(ImGuiMod_Super, key_event->is_meta_pressed());

		// Map Godot keys to ImGui keys
		ImGuiKey imgui_key = ImGuiKey_None;
		Key godot_key = key_event->get_keycode();

		// Basic mapping - a complete implementation would map all keys
		switch (godot_key) {
			case Key::KEY_TAB:
				imgui_key = ImGuiKey_Tab;
				break;
			case Key::KEY_LEFT:
				imgui_key = ImGuiKey_LeftArrow;
				break;
			case Key::KEY_RIGHT:
				imgui_key = ImGuiKey_RightArrow;
				break;
			case Key::KEY_UP:
				imgui_key = ImGuiKey_UpArrow;
				break;
			case Key::KEY_DOWN:
				imgui_key = ImGuiKey_DownArrow;
				break;
			case Key::KEY_PAGEUP:
				imgui_key = ImGuiKey_PageUp;
				break;
			case Key::KEY_PAGEDOWN:
				imgui_key = ImGuiKey_PageDown;
				break;
			case Key::KEY_HOME:
				imgui_key = ImGuiKey_Home;
				break;
			case Key::KEY_END:
				imgui_key = ImGuiKey_End;
				break;
			case Key::KEY_INSERT:
				imgui_key = ImGuiKey_Insert;
				break;
			case Key::KEY_DELETE:
				imgui_key = ImGuiKey_Delete;
				break;
			case Key::KEY_BACKSPACE:
				imgui_key = ImGuiKey_Backspace;
				break;
			case Key::KEY_SPACE:
				imgui_key = ImGuiKey_Space;
				break;
			case Key::KEY_ENTER:
				imgui_key = ImGuiKey_Enter;
				break;
			case Key::KEY_ESCAPE:
				imgui_key = ImGuiKey_Escape;
				break;
			case Key::KEY_A:
				imgui_key = ImGuiKey_A;
				break;
			case Key::KEY_C:
				imgui_key = ImGuiKey_C;
				break;
			case Key::KEY_V:
				imgui_key = ImGuiKey_V;
				break;
			case Key::KEY_X:
				imgui_key = ImGuiKey_X;
				break;
			case Key::KEY_Y:
				imgui_key = ImGuiKey_Y;
				break;
			case Key::KEY_Z:
				imgui_key = ImGuiKey_Z;
				break;
			default:
				break;
		}

		if (imgui_key != ImGuiKey_None) {
			io.AddKeyEvent(imgui_key, key_event->is_pressed());
		}

		// Add text input
		if (key_event->is_pressed() && key_event->get_unicode() != 0) {
			char32_t unicode = key_event->get_unicode();
			if (unicode < 0x10000) {
				io.AddInputCharacter((unsigned short)unicode);
			}
		}
	}
}

void ImGuiGodot::_notification(int p_what) {
	switch (p_what) {
		case NOTIFICATION_DRAW: {
			if (initialized && enabled) {
				render_draw_data();
				queue_redraw();
			}
			break;
		}
	}
}

void SetupImGuiGruvboxHardStyle();
void SetupDarkForestStyle();

void ImGuiGodot::setup_imgui_style() {
	// ImGui::StyleColorsDark();
	SetupImGuiGruvboxHardStyle();
	// SetupDarkForestStyle();
}

void ImGuiGodot::create_fonts_texture() {
	ImGuiIO &io = ImGui::GetIO();

	// Load Roboto Medium as base font (Latin characters)
	io.Fonts->AddFontFromMemoryCompressedTTF(Roboto_Medium_compressed_data, Roboto_Medium_compressed_size, font_size);

	// Merge Chinese font into the default font
	ImFontConfig cjk_cfg;
	cjk_cfg.MergeMode = true;
	cjk_cfg.SizePixels = font_size;

	if (chinese_font_path.is_empty()) {
		// Use embedded SimHei font
		io.Fonts->AddFontFromMemoryCompressedTTF(Simhei_compressed_data, Simhei_compressed_size, font_size, &cjk_cfg, io.Fonts->GetGlyphRangesChineseFull());
	} else {
		// Use user-specified font file
		io.Fonts->AddFontFromFileTTF(chinese_font_path.utf8().get_data(), font_size, &cjk_cfg, io.Fonts->GetGlyphRangesChineseFull());
	}

	unsigned char *pixels;
	int width, height;
	io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);

	// Create Godot Image from ImGui font texture data
	PackedByteArray data;
	data.resize(width * height * 4);
	memcpy(data.ptrw(), pixels, width * height * 4);

	Ref<Image> image = Image::create_from_data(width, height, false, Image::FORMAT_RGBA8, data);

	// Create ImageTexture from Image
	font_texture = ImageTexture::create_from_image(image);

	// Store texture ID in ImGui
	io.Fonts->TexID = (ImTextureID)(uintptr_t)font_texture->get_rid().get_id();
}

static inline Color imgui_col_to_godot(ImU32 col) {
	return Color(
			((col >> IM_COL32_R_SHIFT) & 0xFF) / 255.0f,
			((col >> IM_COL32_G_SHIFT) & 0xFF) / 255.0f,
			((col >> IM_COL32_B_SHIFT) & 0xFF) / 255.0f,
			((col >> IM_COL32_A_SHIFT) & 0xFF) / 255.0f);
}

void ImGuiGodot::render_draw_data() {
	ImDrawData *draw_data = ImGui::GetDrawData();

	if (!draw_data || draw_data->CmdListsCount == 0) {
		return;
	}

	RID ci = get_canvas_item();
	RenderingServer *rs = RenderingServer::get_singleton();

	// Pre-calculate total vertex count to allocate once
	int total_vtx = 0;
	for (int n = 0; n < draw_data->CmdListsCount; n++) {
		total_vtx += draw_data->CmdLists[n]->IdxBuffer.Size;
	}

	PackedVector2Array all_points;
	PackedColorArray all_colors;
	PackedVector2Array all_uvs;
	all_points.resize(total_vtx);
	all_colors.resize(total_vtx);
	all_uvs.resize(total_vtx);

	Vector2 *pts_ptr = all_points.ptrw();
	Color *col_ptr = all_colors.ptrw();
	Vector2 *uv_ptr = all_uvs.ptrw();

	int vtx_offset = 0;
	RID cached_tex_rid = font_texture.is_valid() ? font_texture->get_rid() : RID();

	for (int n = 0; n < draw_data->CmdListsCount; n++) {
		const ImDrawList *cmd_list = draw_data->CmdLists[n];
		const ImDrawVert *vtx_buffer = cmd_list->VtxBuffer.Data;
		const ImDrawIdx *idx_buffer = cmd_list->IdxBuffer.Data;

		for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.Size; cmd_i++) {
			const ImDrawCmd *pcmd = &cmd_list->CmdBuffer[cmd_i];

			if (pcmd->UserCallback) {
				pcmd->UserCallback(cmd_list, pcmd);
				continue;
			}

			if (pcmd->ClipRect.z <= pcmd->ClipRect.x || pcmd->ClipRect.w <= pcmd->ClipRect.y) {
				continue;
			}

			int cmd_start = vtx_offset;

			// Expand indexed vertices into flat buffer
			for (unsigned int i = 0; i < pcmd->ElemCount; i++) {
				const ImDrawVert &v = vtx_buffer[idx_buffer[pcmd->IdxOffset + i]];
				pts_ptr[vtx_offset] = Vector2(v.pos.x, v.pos.y);
				col_ptr[vtx_offset] = imgui_col_to_godot(v.col);
				uv_ptr[vtx_offset] = Vector2(v.uv.x, v.uv.y);
				vtx_offset++;
			}

			int cmd_count = vtx_offset - cmd_start;

			// Build identity index array
			PackedInt32Array indices;
			indices.resize(cmd_count);
			int32_t *idx_ptr = indices.ptrw();
			for (int i = 0; i < cmd_count; i++) {
				idx_ptr[i] = i;
			}

			// Slice view into pre-allocated arrays
			PackedVector2Array cmd_pts;
			PackedColorArray cmd_cols;
			PackedVector2Array cmd_uvs;
			cmd_pts.resize(cmd_count);
			cmd_cols.resize(cmd_count);
			cmd_uvs.resize(cmd_count);
			memcpy(cmd_pts.ptrw(), pts_ptr + cmd_start, cmd_count * sizeof(Vector2));
			memcpy(cmd_cols.ptrw(), col_ptr + cmd_start, cmd_count * sizeof(Color));
			memcpy(cmd_uvs.ptrw(), uv_ptr + cmd_start, cmd_count * sizeof(Vector2));

			// Resolve texture
			ImTextureID tex_id = pcmd->GetTexID();
			RID tex_rid;
			if (tex_id && tex_id == (ImTextureID)(uintptr_t)cached_tex_rid.get_id()) {
				tex_rid = cached_tex_rid;
			}

			rs->canvas_item_add_triangle_array(
					ci, indices, cmd_pts, cmd_cols, cmd_uvs,
					PackedInt32Array(), PackedFloat32Array(),
					tex_rid, -1);
		}
	}
}

void ImGuiGodot::update_mouse_cursor() {
	ImGuiIO &io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_NoMouseCursorChange) {
		return;
	}

	ImGuiMouseCursor imgui_cursor = ImGui::GetMouseCursor();
	// Map ImGui cursor to Godot cursor
}

// Demo, Debug, Information
void ImGuiGodot::show_demo_window(bool show) {
	if (!initialized)
		return;
	if (show) {
		ImGui::ShowDemoWindow();
	}
}

void ImGuiGodot::show_metrics_window(bool show) {
	if (!initialized)
		return;
	if (show) {
		ImGui::ShowMetricsWindow();
	}
}

void ImGuiGodot::show_about_window(bool show) {
	if (!initialized)
		return;
	if (show) {
		ImGui::ShowAboutWindow();
	}
}

void ImGuiGodot::show_style_editor() {
	if (!initialized)
		return;
	ImGui::ShowStyleEditor();
}

// ============================================================================
// GDScript API Wrappers
// ============================================================================

// Window functions
bool ImGuiGodot::begin(const String &name, bool has_close_button) {
	if (!initialized)
		return false;

	if (has_close_button) {
		bool open = true;
		return ImGui::Begin(name.utf8().get_data(), &open);
	} else {
		return ImGui::Begin(name.utf8().get_data(), nullptr);
	}
}

void ImGuiGodot::end() {
	if (!initialized)
		return;
	ImGui::End();
}

bool ImGuiGodot::begin_child(const String &str_id, const Vector2 &size, int child_flags, int window_flags) {
	if (!initialized)
		return false;
	return ImGui::BeginChild(str_id.utf8().get_data(), ImVec2(size.x, size.y), child_flags, window_flags);
}

void ImGuiGodot::end_child() {
	if (!initialized)
		return;
	ImGui::EndChild();
}

// Widgets: Text
void ImGuiGodot::text(const String &text) {
	if (!initialized)
		return;
	ImGui::TextUnformatted(text.utf8().get_data());
}

void ImGuiGodot::text_colored(const Color &color, const String &text) {
	if (!initialized)
		return;
	ImGui::TextColored(ImVec4(color.r, color.g, color.b, color.a), "%s", text.utf8().get_data());
}

void ImGuiGodot::text_disabled(const String &text) {
	if (!initialized)
		return;
	ImGui::TextDisabled("%s", text.utf8().get_data());
}

void ImGuiGodot::text_wrapped(const String &text) {
	if (!initialized)
		return;
	ImGui::TextWrapped("%s", text.utf8().get_data());
}

void ImGuiGodot::label_text(const String &label, const String &text) {
	if (!initialized)
		return;
	ImGui::LabelText(label.utf8().get_data(), "%s", text.utf8().get_data());
}

void ImGuiGodot::bullet_text(const String &text) {
	if (!initialized)
		return;
	ImGui::BulletText("%s", text.utf8().get_data());
}

// Widgets: Main
bool ImGuiGodot::button(const String &label, const Vector2 &size) {
	if (!initialized)
		return false;
	return ImGui::Button(label.utf8().get_data(), ImVec2(size.x, size.y));
}

bool ImGuiGodot::small_button(const String &label) {
	if (!initialized)
		return false;
	return ImGui::SmallButton(label.utf8().get_data());
}

bool ImGuiGodot::checkbox(const String &label, bool value) {
	if (!initialized)
		return value;
	ImGui::Checkbox(label.utf8().get_data(), &value);
	return value;
}

bool ImGuiGodot::radio_button(const String &label, bool active) {
	if (!initialized)
		return false;
	return ImGui::RadioButton(label.utf8().get_data(), active);
}

// Widgets: Sliders
float ImGuiGodot::slider_float(const String &label, float value, float min_value, float max_value) {
	if (!initialized)
		return value;
	ImGui::SliderFloat(label.utf8().get_data(), &value, min_value, max_value);
	return value;
}

int ImGuiGodot::slider_int(const String &label, int value, int min_value, int max_value) {
	if (!initialized)
		return value;
	ImGui::SliderInt(label.utf8().get_data(), &value, min_value, max_value);
	return value;
}

// Widgets: Input
String ImGuiGodot::input_text(const String &label, const String &text, int max_length) {
	if (!initialized)
		return text;

	char *buffer = new char[max_length];
	strncpy(buffer, text.utf8().get_data(), max_length - 1);
	buffer[max_length - 1] = '\0';

	ImGui::InputText(label.utf8().get_data(), buffer, max_length);
	String result = String(buffer);
	delete[] buffer;

	return result;
}

float ImGuiGodot::input_float(const String &label, float value) {
	if (!initialized)
		return value;
	ImGui::InputFloat(label.utf8().get_data(), &value);
	return value;
}

int ImGuiGodot::input_int(const String &label, int value) {
	if (!initialized)
		return value;
	ImGui::InputInt(label.utf8().get_data(), &value);
	return value;
}

// Widgets: Trees
bool ImGuiGodot::tree_node(const String &label) {
	if (!initialized)
		return false;
	return ImGui::TreeNode(label.utf8().get_data());
}

void ImGuiGodot::tree_pop() {
	if (!initialized)
		return;
	ImGui::TreePop();
}

// Widgets: Selectables
bool ImGuiGodot::selectable(const String &label, bool selected) {
	if (!initialized)
		return selected;
	ImGui::Selectable(label.utf8().get_data(), &selected);
	return selected;
}

// Widgets: Combo boxes
bool ImGuiGodot::begin_combo(const String &label, const String &preview_value, int flags) {
	if (!initialized)
		return false;
	return ImGui::BeginCombo(label.utf8().get_data(), preview_value.utf8().get_data(), flags);
}

void ImGuiGodot::end_combo() {
	if (!initialized)
		return;
	ImGui::EndCombo();
}

int ImGuiGodot::combo(const String &label, int current_item, const PackedStringArray &items, int popup_max_height_in_items) {
	if (!initialized)
		return current_item;

	// Convert PackedStringArray to const char* array
	int items_count = items.size();
	const char **items_cstr = new const char *[items_count];
	for (int i = 0; i < items_count; i++) {
		items_cstr[i] = items[i].utf8().get_data();
	}

	ImGui::Combo(label.utf8().get_data(), &current_item, items_cstr, items_count, popup_max_height_in_items);

	delete[] items_cstr;
	return current_item;
}

// Widgets: Drag
float ImGuiGodot::drag_float(const String &label, float value, float v_speed, float v_min, float v_max) {
	if (!initialized)
		return value;
	ImGui::DragFloat(label.utf8().get_data(), &value, v_speed, v_min, v_max);
	return value;
}

int ImGuiGodot::drag_int(const String &label, int value, float v_speed, int v_min, int v_max) {
	if (!initialized)
		return value;
	ImGui::DragInt(label.utf8().get_data(), &value, v_speed, v_min, v_max);
	return value;
}

Vector2 ImGuiGodot::drag_float2(const String &label, const Vector2 &value, float v_speed, float v_min, float v_max) {
	if (!initialized)
		return value;
	float v[2] = { value.x, value.y };
	ImGui::DragFloat2(label.utf8().get_data(), v, v_speed, v_min, v_max);
	return Vector2(v[0], v[1]);
}

Vector3 ImGuiGodot::drag_float3(const String &label, const Vector3 &value, float v_speed, float v_min, float v_max) {
	if (!initialized)
		return value;
	float v[3] = { value.x, value.y, value.z };
	ImGui::DragFloat3(label.utf8().get_data(), v, v_speed, v_min, v_max);
	return Vector3(v[0], v[1], v[2]);
}

// Widgets: Multi-component sliders
Vector2 ImGuiGodot::slider_float2(const String &label, const Vector2 &value, float v_min, float v_max) {
	if (!initialized)
		return value;
	float v[2] = { value.x, value.y };
	ImGui::SliderFloat2(label.utf8().get_data(), v, v_min, v_max);
	return Vector2(v[0], v[1]);
}

Vector3 ImGuiGodot::slider_float3(const String &label, const Vector3 &value, float v_min, float v_max) {
	if (!initialized)
		return value;
	float v[3] = { value.x, value.y, value.z };
	ImGui::SliderFloat3(label.utf8().get_data(), v, v_min, v_max);
	return Vector3(v[0], v[1], v[2]);
}

// Widgets: Color pickers
Color ImGuiGodot::color_edit3(const String &label, const Color &color, int flags) {
	if (!initialized)
		return color;
	float col[3] = { color.r, color.g, color.b };
	ImGui::ColorEdit3(label.utf8().get_data(), col, flags);
	return Color(col[0], col[1], col[2], color.a);
}

Color ImGuiGodot::color_edit4(const String &label, const Color &color, int flags) {
	if (!initialized)
		return color;
	float col[4] = { color.r, color.g, color.b, color.a };
	ImGui::ColorEdit4(label.utf8().get_data(), col, flags);
	return Color(col[0], col[1], col[2], col[3]);
}

Color ImGuiGodot::color_picker3(const String &label, const Color &color, int flags) {
	if (!initialized)
		return color;
	float col[3] = { color.r, color.g, color.b };
	ImGui::ColorPicker3(label.utf8().get_data(), col, flags);
	return Color(col[0], col[1], col[2], color.a);
}

Color ImGuiGodot::color_picker4(const String &label, const Color &color, int flags) {
	if (!initialized)
		return color;
	float col[4] = { color.r, color.g, color.b, color.a };
	ImGui::ColorPicker4(label.utf8().get_data(), col, flags);
	return Color(col[0], col[1], col[2], col[3]);
}

bool ImGuiGodot::color_button(const String &desc_id, const Color &color, int flags, const Vector2 &size) {
	if (!initialized)
		return false;
	return ImGui::ColorButton(desc_id.utf8().get_data(), ImVec4(color.r, color.g, color.b, color.a), flags, ImVec2(size.x, size.y));
}

// Widgets: Misc
bool ImGuiGodot::collapsing_header(const String &label, int flags) {
	if (!initialized)
		return false;
	return ImGui::CollapsingHeader(label.utf8().get_data(), flags);
}

void ImGuiGodot::progress_bar(float fraction, const Vector2 &size, const String &overlay) {
	if (!initialized)
		return;
	const char *overlay_cstr = overlay.is_empty() ? NULL : overlay.utf8().get_data();
	ImGui::ProgressBar(fraction, ImVec2(size.x, size.y), overlay_cstr);
}

void ImGuiGodot::bullet() {
	if (!initialized)
		return;
	ImGui::Bullet();
}

// Menus
bool ImGuiGodot::begin_main_menu_bar() {
	if (!initialized)
		return false;
	return ImGui::BeginMainMenuBar();
}

void ImGuiGodot::end_main_menu_bar() {
	if (!initialized)
		return;
	ImGui::EndMainMenuBar();
}

bool ImGuiGodot::begin_menu_bar() {
	if (!initialized)
		return false;
	return ImGui::BeginMenuBar();
}

void ImGuiGodot::end_menu_bar() {
	if (!initialized)
		return;
	ImGui::EndMenuBar();
}

bool ImGuiGodot::begin_menu(const String &label, bool enabled) {
	if (!initialized)
		return false;
	return ImGui::BeginMenu(label.utf8().get_data(), enabled);
}

void ImGuiGodot::end_menu() {
	if (!initialized)
		return;
	ImGui::EndMenu();
}

bool ImGuiGodot::menu_item(const String &label, const String &shortcut, bool selected, bool enabled) {
	if (!initialized)
		return false;
	const char *shortcut_cstr = shortcut.is_empty() ? NULL : shortcut.utf8().get_data();
	return ImGui::MenuItem(label.utf8().get_data(), shortcut_cstr, selected, enabled);
}

// Popups
void ImGuiGodot::open_popup(const String &str_id, int popup_flags) {
	if (!initialized)
		return;
	ImGui::OpenPopup(str_id.utf8().get_data(), popup_flags);
}

bool ImGuiGodot::begin_popup(const String &str_id, int window_flags) {
	if (!initialized)
		return false;
	return ImGui::BeginPopup(str_id.utf8().get_data(), window_flags);
}

bool ImGuiGodot::begin_popup_modal(const String &name, bool has_close_button, int window_flags) {
	if (!initialized)
		return false;
	if (has_close_button) {
		bool open = true;
		return ImGui::BeginPopupModal(name.utf8().get_data(), &open, window_flags);
	} else {
		return ImGui::BeginPopupModal(name.utf8().get_data(), nullptr, window_flags);
	}
}

void ImGuiGodot::end_popup() {
	if (!initialized)
		return;
	ImGui::EndPopup();
}

void ImGuiGodot::close_current_popup() {
	if (!initialized)
		return;
	ImGui::CloseCurrentPopup();
}

// Tooltips
bool ImGuiGodot::begin_tooltip() {
	if (!initialized)
		return false;
	return ImGui::BeginTooltip();
}

void ImGuiGodot::end_tooltip() {
	if (!initialized)
		return;
	ImGui::EndTooltip();
}

void ImGuiGodot::set_tooltip(const String &text) {
	if (!initialized)
		return;
	ImGui::SetTooltip("%s", text.utf8().get_data());
}

// Tables
bool ImGuiGodot::begin_table(const String &str_id, int columns, int flags, const Vector2 &outer_size, float inner_width) {
	if (!initialized)
		return false;
	return ImGui::BeginTable(str_id.utf8().get_data(), columns, flags, ImVec2(outer_size.x, outer_size.y), inner_width);
}

void ImGuiGodot::end_table() {
	if (!initialized)
		return;
	ImGui::EndTable();
}

void ImGuiGodot::table_next_row(int row_flags, float min_row_height) {
	if (!initialized)
		return;
	ImGui::TableNextRow(row_flags, min_row_height);
}

bool ImGuiGodot::table_next_column() {
	if (!initialized)
		return false;
	return ImGui::TableNextColumn();
}

bool ImGuiGodot::table_set_column_index(int column_n) {
	if (!initialized)
		return false;
	return ImGui::TableSetColumnIndex(column_n);
}

void ImGuiGodot::table_setup_column(const String &label, int flags, float init_width_or_weight, int user_id) {
	if (!initialized)
		return;
	ImGui::TableSetupColumn(label.utf8().get_data(), flags, init_width_or_weight, user_id);
}

void ImGuiGodot::table_headers_row() {
	if (!initialized)
		return;
	ImGui::TableHeadersRow();
}

// Tab bars
bool ImGuiGodot::begin_tab_bar(const String &str_id, int flags) {
	if (!initialized)
		return false;
	return ImGui::BeginTabBar(str_id.utf8().get_data(), flags);
}

void ImGuiGodot::end_tab_bar() {
	if (!initialized)
		return;
	ImGui::EndTabBar();
}

bool ImGuiGodot::begin_tab_item(const String &label, bool has_close_button, int flags) {
	if (!initialized)
		return false;
	if (has_close_button) {
		bool open = true;
		return ImGui::BeginTabItem(label.utf8().get_data(), &open, flags);
	} else {
		return ImGui::BeginTabItem(label.utf8().get_data(), nullptr, flags);
	}
}

void ImGuiGodot::end_tab_item() {
	if (!initialized)
		return;
	ImGui::EndTabItem();
}

// Layout
void ImGuiGodot::separator() {
	if (!initialized)
		return;
	ImGui::Separator();
}

void ImGuiGodot::separator_text(const String &label) {
	if (!initialized)
		return;
	ImGui::SeparatorText(label.utf8().get_data());
}

void ImGuiGodot::same_line(float offset_from_start_x, float spacing) {
	if (!initialized)
		return;
	ImGui::SameLine(offset_from_start_x, spacing);
}

void ImGuiGodot::new_line() {
	if (!initialized)
		return;
	ImGui::NewLine();
}

void ImGuiGodot::spacing() {
	if (!initialized)
		return;
	ImGui::Spacing();
}

void ImGuiGodot::dummy(const Vector2 &size) {
	if (!initialized)
		return;
	ImGui::Dummy(ImVec2(size.x, size.y));
}

void ImGuiGodot::indent(float indent_w) {
	if (!initialized)
		return;
	ImGui::Indent(indent_w);
}

void ImGuiGodot::unindent(float indent_w) {
	if (!initialized)
		return;
	ImGui::Unindent(indent_w);
}

void ImGuiGodot::begin_group() {
	if (!initialized)
		return;
	ImGui::BeginGroup();
}

void ImGuiGodot::end_group() {
	if (!initialized)
		return;
	ImGui::EndGroup();
}

Vector2 ImGuiGodot::get_content_region_avail() {
	if (!initialized)
		return Vector2(0, 0);
	ImVec2 avail = ImGui::GetContentRegionAvail();
	return Vector2(avail.x, avail.y);
}

Vector2 ImGuiGodot::get_cursor_screen_pos() {
	if (!initialized)
		return Vector2(0, 0);
	ImVec2 pos = ImGui::GetCursorScreenPos();
	return Vector2(pos.x, pos.y);
}

void ImGuiGodot::set_cursor_screen_pos(const Vector2 &pos) {
	if (!initialized)
		return;
	ImGui::SetCursorScreenPos(ImVec2(pos.x, pos.y));
}

// Cursor / Layout
Vector2 ImGuiGodot::get_cursor_pos() {
	if (!initialized)
		return Vector2(0, 0);
	ImVec2 pos = ImGui::GetCursorPos();
	return Vector2(pos.x, pos.y);
}

void ImGuiGodot::set_cursor_pos(const Vector2 &pos) {
	if (!initialized)
		return;
	ImGui::SetCursorPos(ImVec2(pos.x, pos.y));
}

float ImGuiGodot::get_cursor_pos_x() {
	if (!initialized)
		return 0.0f;
	return ImGui::GetCursorPosX();
}

float ImGuiGodot::get_cursor_pos_y() {
	if (!initialized)
		return 0.0f;
	return ImGui::GetCursorPosY();
}

void ImGuiGodot::set_cursor_pos_x(float x) {
	if (!initialized)
		return;
	ImGui::SetCursorPosX(x);
}

void ImGuiGodot::set_cursor_pos_y(float y) {
	if (!initialized)
		return;
	ImGui::SetCursorPosY(y);
}

// ID stack
void ImGuiGodot::push_id(const String &id) {
	if (!initialized)
		return;
	ImGui::PushID(id.utf8().get_data());
}

void ImGuiGodot::pop_id() {
	if (!initialized)
		return;
	ImGui::PopID();
}

// Style
void ImGuiGodot::push_style_color(int idx, const Color &color) {
	if (!initialized)
		return;
	ImGui::PushStyleColor(idx, ImVec4(color.r, color.g, color.b, color.a));
}

void ImGuiGodot::pop_style_color(int count) {
	if (!initialized)
		return;
	ImGui::PopStyleColor(count);
}

void ImGuiGodot::push_style_var_float(int idx, float val) {
	if (!initialized)
		return;
	ImGui::PushStyleVar(idx, val);
}

void ImGuiGodot::push_style_var_vec2(int idx, const Vector2 &val) {
	if (!initialized)
		return;
	ImGui::PushStyleVar(idx, ImVec2(val.x, val.y));
}

void ImGuiGodot::pop_style_var(int count) {
	if (!initialized)
		return;
	ImGui::PopStyleVar(count);
}

// Item/Widget utilities
bool ImGuiGodot::is_item_hovered(int flags) {
	if (!initialized)
		return false;
	return ImGui::IsItemHovered(flags);
}

bool ImGuiGodot::is_item_active() {
	if (!initialized)
		return false;
	return ImGui::IsItemActive();
}

bool ImGuiGodot::is_item_focused() {
	if (!initialized)
		return false;
	return ImGui::IsItemFocused();
}

bool ImGuiGodot::is_item_clicked(int mouse_button) {
	if (!initialized)
		return false;
	return ImGui::IsItemClicked(mouse_button);
}

bool ImGuiGodot::is_item_visible() {
	if (!initialized)
		return false;
	return ImGui::IsItemVisible();
}

bool ImGuiGodot::is_item_edited() {
	if (!initialized)
		return false;
	return ImGui::IsItemEdited();
}

bool ImGuiGodot::is_item_activated() {
	if (!initialized)
		return false;
	return ImGui::IsItemActivated();
}

bool ImGuiGodot::is_item_deactivated() {
	if (!initialized)
		return false;
	return ImGui::IsItemDeactivated();
}

bool ImGuiGodot::is_item_deactivated_after_edit() {
	if (!initialized)
		return false;
	return ImGui::IsItemDeactivatedAfterEdit();
}

Vector2 ImGuiGodot::get_item_rect_min() {
	if (!initialized)
		return Vector2(0, 0);
	ImVec2 rect = ImGui::GetItemRectMin();
	return Vector2(rect.x, rect.y);
}

Vector2 ImGuiGodot::get_item_rect_max() {
	if (!initialized)
		return Vector2(0, 0);
	ImVec2 rect = ImGui::GetItemRectMax();
	return Vector2(rect.x, rect.y);
}

Vector2 ImGuiGodot::get_item_rect_size() {
	if (!initialized)
		return Vector2(0, 0);
	ImVec2 size = ImGui::GetItemRectSize();
	return Vector2(size.x, size.y);
}

// Window utilities
bool ImGuiGodot::is_window_appearing() {
	if (!initialized)
		return false;
	return ImGui::IsWindowAppearing();
}

bool ImGuiGodot::is_window_collapsed() {
	if (!initialized)
		return false;
	return ImGui::IsWindowCollapsed();
}

bool ImGuiGodot::is_window_focused(int flags) {
	if (!initialized)
		return false;
	return ImGui::IsWindowFocused(flags);
}

bool ImGuiGodot::is_window_hovered(int flags) {
	if (!initialized)
		return false;
	return ImGui::IsWindowHovered(flags);
}

Vector2 ImGuiGodot::get_window_pos() {
	if (!initialized)
		return Vector2(0, 0);
	ImVec2 pos = ImGui::GetWindowPos();
	return Vector2(pos.x, pos.y);
}

Vector2 ImGuiGodot::get_window_size() {
	if (!initialized)
		return Vector2(0, 0);
	ImVec2 size = ImGui::GetWindowSize();
	return Vector2(size.x, size.y);
}

float ImGuiGodot::get_window_width() {
	if (!initialized)
		return 0.0f;
	return ImGui::GetWindowWidth();
}

float ImGuiGodot::get_window_height() {
	if (!initialized)
		return 0.0f;
	return ImGui::GetWindowHeight();
}

// Miscellaneous utilities
bool ImGuiGodot::is_mouse_down(int button) {
	if (!initialized)
		return false;
	return ImGui::IsMouseDown(button);
}

bool ImGuiGodot::is_mouse_clicked(int button, bool repeat) {
	if (!initialized)
		return false;
	return ImGui::IsMouseClicked(button, repeat);
}

bool ImGuiGodot::is_mouse_double_clicked(int button) {
	if (!initialized)
		return false;
	return ImGui::IsMouseDoubleClicked(button);
}

Vector2 ImGuiGodot::get_mouse_pos() {
	if (!initialized)
		return Vector2(0, 0);
	ImVec2 pos = ImGui::GetMousePos();
	return Vector2(pos.x, pos.y);
}

void ImGuiGodot::set_next_window_pos(const Vector2 &pos, int cond, const Vector2 &pivot) {
	if (!initialized)
		return;
	ImGui::SetNextWindowPos(ImVec2(pos.x, pos.y), cond, ImVec2(pivot.x, pivot.y));
}

void ImGuiGodot::set_next_window_size(const Vector2 &size, int cond) {
	if (!initialized)
		return;
	ImGui::SetNextWindowSize(ImVec2(size.x, size.y), cond);
}

void ImGuiGodot::set_next_window_collapsed(bool collapsed, int cond) {
	if (!initialized)
		return;
	ImGui::SetNextWindowCollapsed(collapsed, cond);
}

void ImGuiGodot::set_next_window_focus() {
	if (!initialized)
		return;
	ImGui::SetNextWindowFocus();
}

// Enable/disable
void ImGuiGodot::set_enabled(bool p_enabled) {
	enabled = p_enabled;
}

bool ImGuiGodot::is_enabled() const {
	return enabled;
}

// Font configuration
void ImGuiGodot::set_chinese_font_path(const String &path) {
	chinese_font_path = path;
}

void ImGuiGodot::set_font_size(float size) {
	if (size > 0.0f) {
		font_size = size;
	}
}

// themes

void SetupImGuiGruvboxHardStyle()
{
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    // --- 1. Sizing and Spacing (Industrial & Square) ---
    style.WindowPadding = ImVec2(10.0f, 10.0f);
    style.FramePadding = ImVec2(6.0f, 4.0f);
    style.ItemSpacing = ImVec2(8.0f, 4.0f);
    style.ScrollbarSize = 14.0f;
    style.GrabMinSize = 12.0f;

    // --- 2. Borders & Rounding (Gruvbox usually looks best with sharp or low rounding) ---
    style.WindowRounding = 2.0f;
    style.FrameRounding = 2.0f;
    style.PopupRounding = 2.0f;
    style.ScrollbarRounding = 2.0f;
    style.GrabRounding = 2.0f;
    style.TabRounding = 2.0f;

    style.WindowBorderSize = 1.0f;
    style.FrameBorderSize = 1.0f;
    style.PopupBorderSize = 1.0f;

    // --- 3. The Gruvbox Dark Hard Palette ---
    // Background: #1d2021 (Dark Hard) | Foreground: #ebdbb2
    // Red: #fb4934 | Green: #b8bb26 | Yellow: #fabd2f | Blue: #83a598
    // Gray: #928374 | Orange: #fe8019

    // Text
    colors[ImGuiCol_Text] = ImVec4(0.92f, 0.86f, 0.70f, 1.00f); // #ebdbb2
    colors[ImGuiCol_TextDisabled] = ImVec4(0.57f, 0.51f, 0.45f, 1.00f); // #928374

    // Backgrounds
    colors[ImGuiCol_WindowBg] = ImVec4(0.11f, 0.13f, 0.13f, 1.00f); // #1d2021
    colors[ImGuiCol_ChildBg] = ImVec4(0.11f, 0.13f, 0.13f, 0.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.11f, 0.13f, 0.13f, 0.95f);

    // Borders
    colors[ImGuiCol_Border] = ImVec4(0.31f, 0.29f, 0.27f, 1.00f); // #504945
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

    // Frames
    colors[ImGuiCol_FrameBg] = ImVec4(0.24f, 0.22f, 0.21f, 1.00f); // #3c3836
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.31f, 0.29f, 0.27f, 1.00f); // #504945
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.40f, 0.36f, 0.33f, 1.00f); // #665c54

    // Title Bars
    colors[ImGuiCol_TitleBg] = ImVec4(0.11f, 0.13f, 0.13f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.11f, 0.13f, 0.13f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.11f, 0.13f, 0.13f, 1.00f);

    // Menus
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.15f, 0.14f, 0.13f, 1.00f); // #282828

    // Scrollbars
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.11f, 0.13f, 0.13f, 1.00f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.29f, 0.27f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.36f, 0.33f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.57f, 0.51f, 0.45f, 1.00f);

    // Interactables
    colors[ImGuiCol_CheckMark] = ImVec4(0.72f, 0.73f, 0.15f, 1.00f); // #b8bb26 (Green)
    colors[ImGuiCol_SliderGrab] = ImVec4(0.51f, 0.65f, 0.60f, 1.00f); // #83a598 (Blue)
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.55f, 0.73f, 0.67f, 1.00f);
    colors[ImGuiCol_Button] = ImVec4(0.31f, 0.29f, 0.27f, 1.00f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.98f, 0.29f, 0.20f, 1.00f); // #fb4934 (Red)
    colors[ImGuiCol_ButtonActive] = ImVec4(0.80f, 0.20f, 0.15f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.24f, 0.22f, 0.21f, 1.00f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.31f, 0.29f, 0.27f, 1.00f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.40f, 0.36f, 0.33f, 1.00f);

    // Tabs
    colors[ImGuiCol_Tab] = ImVec4(0.24f, 0.22f, 0.21f, 1.00f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.31f, 0.29f, 0.27f, 1.00f);
    colors[ImGuiCol_TabActive] = ImVec4(0.31f, 0.29f, 0.27f, 1.00f);

    // Misc
    colors[ImGuiCol_PlotLines] = ImVec4(0.98f, 0.74f, 0.18f, 1.00f); // #fabd2f (Yellow)
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.31f, 0.29f, 0.27f, 1.00f);
    colors[ImGuiCol_NavHighlight] = ImVec4(0.98f, 0.29f, 0.20f, 1.00f);

#ifdef IMGUI_HAS_DOCK
    colors[ImGuiCol_DockingPreview] = ImVec4(0.72f, 0.73f, 0.15f, 0.50f);
    colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.11f, 0.13f, 0.13f, 1.00f);
#endif
}

void SetupDarkForestStyle()
{
	ImGuiStyle* style = &ImGui::GetStyle();

	style->WindowPadding = ImVec2(15, 15);
	style->WindowRounding = 5.0f;
	style->FramePadding = ImVec2(5, 5);
	style->FrameRounding = 4.0f;
	style->ItemSpacing = ImVec2(12, 8);
	style->ItemInnerSpacing = ImVec2(8, 6);
	style->IndentSpacing = 25.0f;
	style->ScrollbarSize = 15.0f;
	style->ScrollbarRounding = 9.0f;
	style->GrabMinSize = 5.0f;
	style->GrabRounding = 3.0f;

	style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.90f, 0.95f, 1.00f);
	style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.60f, 0.65f, 1.00f);
	style->Colors[ImGuiCol_WindowBg] = ImVec4(0.02f, 0.05f, 0.10f, 1.00f);
	style->Colors[ImGuiCol_PopupBg] = ImVec4(0.05f, 0.10f, 0.15f, 1.00f);
	style->Colors[ImGuiCol_Border] = ImVec4(0.30f, 0.60f, 0.80f, 0.88f);
	style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.20f, 0.50f, 0.70f, 0.00f);
	style->Colors[ImGuiCol_FrameBg] = ImVec4(0.05f, 0.10f, 0.15f, 1.00f);
	style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.10f, 0.20f, 0.30f, 1.00f);
	style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.20f, 0.40f, 0.60f, 1.00f);
	style->Colors[ImGuiCol_TitleBg] = ImVec4(0.05f, 0.10f, 0.15f, 1.00f);
	style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.80f, 0.90f, 0.95f, 0.75f);
	style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.02f, 0.05f, 0.10f, 1.00f);
	style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.05f, 0.10f, 0.15f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.05f, 0.10f, 0.15f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.30f, 0.60f, 0.80f, 0.31f);
	style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.20f, 0.40f, 0.60f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.02f, 0.05f, 0.10f, 1.00f);
	style->Colors[ImGuiCol_CheckMark] = ImVec4(0.30f, 0.60f, 0.80f, 0.31f);
	style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.30f, 0.60f, 0.80f, 0.31f);
	style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.02f, 0.05f, 0.10f, 1.00f);
	style->Colors[ImGuiCol_Button] = ImVec4(0.05f, 0.10f, 0.15f, 1.00f);
	style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.10f, 0.20f, 0.30f, 1.00f);
	style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.40f, 0.60f, 1.00f);
	style->Colors[ImGuiCol_Header] = ImVec4(0.05f, 0.10f, 0.15f, 1.00f);
	style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.20f, 0.40f, 0.60f, 1.00f);
	style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.02f, 0.05f, 0.10f, 1.00f);
	style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.20f, 0.40f, 0.60f, 1.00f);
	style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.20f, 0.40f, 0.60f, 1.00f);
	style->Colors[ImGuiCol_PlotLines] = ImVec4(0.20f, 0.40f, 0.60f, 0.63f);
	style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.30f, 0.60f, 0.80f, 1.00f);
	style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.20f, 0.40f, 0.60f, 0.63f);
	style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.30f, 0.60f, 0.80f, 1.00f);
	style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.00f, 0.50f, 0.50f, 0.43f);
	style->Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.50f, 0.70f, 0.90f, 0.78f);
	style->Colors[ImGuiCol_SeparatorActive] = ImVec4(0.40f, 0.60f, 0.80f, 1.00f);
	style->Colors[ImGuiCol_Tab] = ImVec4(0.20f, 0.40f, 0.60f, 0.86f);
	style->Colors[ImGuiCol_TabHovered] = ImVec4(0.30f, 0.60f, 0.80f, 0.80f);
	style->Colors[ImGuiCol_TabActive] = ImVec4(0.30f, 0.60f, 0.80f, 1.00f);
	style->Colors[ImGuiCol_TabUnfocused] = ImVec4(0.40f, 0.60f, 0.80f, 0.97f);
	style->Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.50f, 0.70f, 0.90f, 1.00f);
	style->Colors[ImGuiCol_DockingPreview] = ImVec4(0.70f, 0.90f, 0.95f, 1.00f);

#ifdef IMGUI_HAS_DOCK
    style->Colors[ImGuiCol_DockingPreview] = ImVec4(0.30f, 0.60f, 0.80f, 0.50f);
    style->Colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.05f, 0.10f, 0.15f, 1.00f);
#endif
}
