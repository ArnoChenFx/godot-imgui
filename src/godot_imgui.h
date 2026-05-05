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
#include <godot_cpp/core/binder_common.hpp>

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

	// =========================================================================
	// Enum Definitions for GDScript
	// =========================================================================

	// --- Bitfield Flags ---

	enum WindowFlags {
		WINDOW_FLAGS_NONE = ImGuiWindowFlags_None,
		WINDOW_FLAGS_NO_TITLE_BAR = ImGuiWindowFlags_NoTitleBar,
		WINDOW_FLAGS_NO_RESIZE = ImGuiWindowFlags_NoResize,
		WINDOW_FLAGS_NO_MOVE = ImGuiWindowFlags_NoMove,
		WINDOW_FLAGS_NO_SCROLLBAR = ImGuiWindowFlags_NoScrollbar,
		WINDOW_FLAGS_NO_SCROLL_WITH_MOUSE = ImGuiWindowFlags_NoScrollWithMouse,
		WINDOW_FLAGS_NO_COLLAPSE = ImGuiWindowFlags_NoCollapse,
		WINDOW_FLAGS_ALWAYS_AUTO_RESIZE = ImGuiWindowFlags_AlwaysAutoResize,
		WINDOW_FLAGS_NO_BACKGROUND = ImGuiWindowFlags_NoBackground,
		WINDOW_FLAGS_NO_SAVED_SETTINGS = ImGuiWindowFlags_NoSavedSettings,
		WINDOW_FLAGS_NO_MOUSE_INPUTS = ImGuiWindowFlags_NoMouseInputs,
		WINDOW_FLAGS_MENU_BAR = ImGuiWindowFlags_MenuBar,
		WINDOW_FLAGS_HORIZONTAL_SCROLLBAR = ImGuiWindowFlags_HorizontalScrollbar,
		WINDOW_FLAGS_NO_FOCUS_ON_APPEARING = ImGuiWindowFlags_NoFocusOnAppearing,
		WINDOW_FLAGS_NO_BRING_TO_FRONT_ON_FOCUS = ImGuiWindowFlags_NoBringToFrontOnFocus,
		WINDOW_FLAGS_ALWAYS_VERTICAL_SCROLLBAR = ImGuiWindowFlags_AlwaysVerticalScrollbar,
		WINDOW_FLAGS_ALWAYS_HORIZONTAL_SCROLLBAR = ImGuiWindowFlags_AlwaysHorizontalScrollbar,
		WINDOW_FLAGS_NO_NAV_INPUTS = ImGuiWindowFlags_NoNavInputs,
		WINDOW_FLAGS_NO_NAV_FOCUS = ImGuiWindowFlags_NoNavFocus,
		WINDOW_FLAGS_UNSAVED_DOCUMENT = ImGuiWindowFlags_UnsavedDocument,
		WINDOW_FLAGS_NO_DOCKING = ImGuiWindowFlags_NoDocking,
		WINDOW_FLAGS_NO_NAV = ImGuiWindowFlags_NoNav,
		WINDOW_FLAGS_NO_DECORATION = ImGuiWindowFlags_NoDecoration,
		WINDOW_FLAGS_NO_INPUTS = ImGuiWindowFlags_NoInputs,
	};

	enum ChildFlags {
		CHILD_FLAGS_NONE = ImGuiChildFlags_None,
		CHILD_FLAGS_BORDERS = ImGuiChildFlags_Borders,
		CHILD_FLAGS_ALWAYS_USE_WINDOW_PADDING = ImGuiChildFlags_AlwaysUseWindowPadding,
		CHILD_FLAGS_RESIZE_X = ImGuiChildFlags_ResizeX,
		CHILD_FLAGS_RESIZE_Y = ImGuiChildFlags_ResizeY,
		CHILD_FLAGS_AUTO_RESIZE_X = ImGuiChildFlags_AutoResizeX,
		CHILD_FLAGS_AUTO_RESIZE_Y = ImGuiChildFlags_AutoResizeY,
		CHILD_FLAGS_ALWAYS_AUTO_RESIZE = ImGuiChildFlags_AlwaysAutoResize,
		CHILD_FLAGS_FRAME_STYLE = ImGuiChildFlags_FrameStyle,
		CHILD_FLAGS_NAV_FLATTENED = ImGuiChildFlags_NavFlattened,
	};

	enum ColorEditFlags {
		COLOR_EDIT_FLAGS_NONE = ImGuiColorEditFlags_None,
		COLOR_EDIT_FLAGS_NO_ALPHA = ImGuiColorEditFlags_NoAlpha,
		COLOR_EDIT_FLAGS_NO_PICKER = ImGuiColorEditFlags_NoPicker,
		COLOR_EDIT_FLAGS_NO_OPTIONS = ImGuiColorEditFlags_NoOptions,
		COLOR_EDIT_FLAGS_NO_SMALL_PREVIEW = ImGuiColorEditFlags_NoSmallPreview,
		COLOR_EDIT_FLAGS_NO_INPUTS = ImGuiColorEditFlags_NoInputs,
		COLOR_EDIT_FLAGS_NO_TOOLTIP = ImGuiColorEditFlags_NoTooltip,
		COLOR_EDIT_FLAGS_NO_LABEL = ImGuiColorEditFlags_NoLabel,
		COLOR_EDIT_FLAGS_NO_SIDE_PREVIEW = ImGuiColorEditFlags_NoSidePreview,
		COLOR_EDIT_FLAGS_NO_DRAG_DROP = ImGuiColorEditFlags_NoDragDrop,
		COLOR_EDIT_FLAGS_NO_BORDER = ImGuiColorEditFlags_NoBorder,
		COLOR_EDIT_FLAGS_NO_COLOR_MARKERS = ImGuiColorEditFlags_NoColorMarkers,
		COLOR_EDIT_FLAGS_ALPHA_OPAQUE = ImGuiColorEditFlags_AlphaOpaque,
		COLOR_EDIT_FLAGS_ALPHA_NO_BG = ImGuiColorEditFlags_AlphaNoBg,
		COLOR_EDIT_FLAGS_ALPHA_PREVIEW_HALF = ImGuiColorEditFlags_AlphaPreviewHalf,
		COLOR_EDIT_FLAGS_ALPHA_BAR = ImGuiColorEditFlags_AlphaBar,
		COLOR_EDIT_FLAGS_HDR = ImGuiColorEditFlags_HDR,
		COLOR_EDIT_FLAGS_DISPLAY_RGB = ImGuiColorEditFlags_DisplayRGB,
		COLOR_EDIT_FLAGS_DISPLAY_HSV = ImGuiColorEditFlags_DisplayHSV,
		COLOR_EDIT_FLAGS_DISPLAY_HEX = ImGuiColorEditFlags_DisplayHex,
		COLOR_EDIT_FLAGS_UINT8 = ImGuiColorEditFlags_Uint8,
		COLOR_EDIT_FLAGS_FLOAT = ImGuiColorEditFlags_Float,
		COLOR_EDIT_FLAGS_PICKER_HUE_BAR = ImGuiColorEditFlags_PickerHueBar,
		COLOR_EDIT_FLAGS_PICKER_HUE_WHEEL = ImGuiColorEditFlags_PickerHueWheel,
		COLOR_EDIT_FLAGS_INPUT_RGB = ImGuiColorEditFlags_InputRGB,
		COLOR_EDIT_FLAGS_INPUT_HSV = ImGuiColorEditFlags_InputHSV,
	};

	enum ComboFlags {
		COMBO_FLAGS_NONE = ImGuiComboFlags_None,
		COMBO_FLAGS_POPUP_ALIGN_LEFT = ImGuiComboFlags_PopupAlignLeft,
		COMBO_FLAGS_HEIGHT_SMALL = ImGuiComboFlags_HeightSmall,
		COMBO_FLAGS_HEIGHT_REGULAR = ImGuiComboFlags_HeightRegular,
		COMBO_FLAGS_HEIGHT_LARGE = ImGuiComboFlags_HeightLarge,
		COMBO_FLAGS_HEIGHT_LARGEST = ImGuiComboFlags_HeightLargest,
		COMBO_FLAGS_NO_ARROW_BUTTON = ImGuiComboFlags_NoArrowButton,
		COMBO_FLAGS_NO_PREVIEW = ImGuiComboFlags_NoPreview,
		COMBO_FLAGS_WIDTH_FIT_PREVIEW = ImGuiComboFlags_WidthFitPreview,
	};

	enum TreeNodeFlags {
		TREE_NODE_FLAGS_NONE = ImGuiTreeNodeFlags_None,
		TREE_NODE_FLAGS_SELECTED = ImGuiTreeNodeFlags_Selected,
		TREE_NODE_FLAGS_FRAMED = ImGuiTreeNodeFlags_Framed,
		TREE_NODE_FLAGS_ALLOW_OVERLAP = ImGuiTreeNodeFlags_AllowOverlap,
		TREE_NODE_FLAGS_NO_TREE_PUSH_ON_OPEN = ImGuiTreeNodeFlags_NoTreePushOnOpen,
		TREE_NODE_FLAGS_NO_AUTO_OPEN_ON_LOG = ImGuiTreeNodeFlags_NoAutoOpenOnLog,
		TREE_NODE_FLAGS_DEFAULT_OPEN = ImGuiTreeNodeFlags_DefaultOpen,
		TREE_NODE_FLAGS_OPEN_ON_DOUBLE_CLICK = ImGuiTreeNodeFlags_OpenOnDoubleClick,
		TREE_NODE_FLAGS_OPEN_ON_ARROW = ImGuiTreeNodeFlags_OpenOnArrow,
		TREE_NODE_FLAGS_LEAF = ImGuiTreeNodeFlags_Leaf,
		TREE_NODE_FLAGS_BULLET = ImGuiTreeNodeFlags_Bullet,
		TREE_NODE_FLAGS_FRAME_PADDING = ImGuiTreeNodeFlags_FramePadding,
		TREE_NODE_FLAGS_SPAN_AVAIL_WIDTH = ImGuiTreeNodeFlags_SpanAvailWidth,
		TREE_NODE_FLAGS_SPAN_FULL_WIDTH = ImGuiTreeNodeFlags_SpanFullWidth,
		TREE_NODE_FLAGS_SPAN_LABEL_WIDTH = ImGuiTreeNodeFlags_SpanLabelWidth,
		TREE_NODE_FLAGS_SPAN_ALL_COLUMNS = ImGuiTreeNodeFlags_SpanAllColumns,
		TREE_NODE_FLAGS_LABEL_SPAN_ALL_COLUMNS = ImGuiTreeNodeFlags_LabelSpanAllColumns,
		TREE_NODE_FLAGS_NAV_LEFT_JUMPS_TO_PARENT = ImGuiTreeNodeFlags_NavLeftJumpsToParent,
		TREE_NODE_FLAGS_COLLAPSING_HEADER = ImGuiTreeNodeFlags_CollapsingHeader,
	};

	enum PopupFlags {
		POPUP_FLAGS_NONE = ImGuiPopupFlags_None,
		POPUP_FLAGS_MOUSE_BUTTON_LEFT = ImGuiPopupFlags_MouseButtonLeft,
		POPUP_FLAGS_MOUSE_BUTTON_RIGHT = ImGuiPopupFlags_MouseButtonRight,
		POPUP_FLAGS_MOUSE_BUTTON_MIDDLE = ImGuiPopupFlags_MouseButtonMiddle,
		POPUP_FLAGS_NO_REOPEN = ImGuiPopupFlags_NoReopen,
		POPUP_FLAGS_NO_OPEN_OVER_EXISTING_POPUP = ImGuiPopupFlags_NoOpenOverExistingPopup,
		POPUP_FLAGS_NO_OPEN_OVER_ITEMS = ImGuiPopupFlags_NoOpenOverItems,
		POPUP_FLAGS_ANY_POPUP_ID = ImGuiPopupFlags_AnyPopupId,
		POPUP_FLAGS_ANY_POPUP_LEVEL = ImGuiPopupFlags_AnyPopupLevel,
		POPUP_FLAGS_ANY_POPUP = ImGuiPopupFlags_AnyPopup,
	};

	enum FocusedFlags {
		FOCUSED_FLAGS_NONE = ImGuiFocusedFlags_None,
		FOCUSED_FLAGS_CHILD_WINDOWS = ImGuiFocusedFlags_ChildWindows,
		FOCUSED_FLAGS_ROOT_WINDOW = ImGuiFocusedFlags_RootWindow,
		FOCUSED_FLAGS_ANY_WINDOW = ImGuiFocusedFlags_AnyWindow,
		FOCUSED_FLAGS_NO_POPUP_HIERARCHY = ImGuiFocusedFlags_NoPopupHierarchy,
		FOCUSED_FLAGS_DOCK_HIERARCHY = ImGuiFocusedFlags_DockHierarchy,
		FOCUSED_FLAGS_ROOT_AND_CHILD_WINDOWS = ImGuiFocusedFlags_RootAndChildWindows,
	};

	enum HoveredFlags {
		HOVERED_FLAGS_NONE = ImGuiHoveredFlags_None,
		HOVERED_FLAGS_CHILD_WINDOWS = ImGuiHoveredFlags_ChildWindows,
		HOVERED_FLAGS_ROOT_WINDOW = ImGuiHoveredFlags_RootWindow,
		HOVERED_FLAGS_ANY_WINDOW = ImGuiHoveredFlags_AnyWindow,
		HOVERED_FLAGS_NO_POPUP_HIERARCHY = ImGuiHoveredFlags_NoPopupHierarchy,
		HOVERED_FLAGS_DOCK_HIERARCHY = ImGuiHoveredFlags_DockHierarchy,
		HOVERED_FLAGS_ALLOW_WHEN_BLOCKED_BY_POPUP = ImGuiHoveredFlags_AllowWhenBlockedByPopup,
		HOVERED_FLAGS_ALLOW_WHEN_BLOCKED_BY_ACTIVE_ITEM = ImGuiHoveredFlags_AllowWhenBlockedByActiveItem,
		HOVERED_FLAGS_ALLOW_WHEN_OVERLAPPED_BY_ITEM = ImGuiHoveredFlags_AllowWhenOverlappedByItem,
		HOVERED_FLAGS_ALLOW_WHEN_OVERLAPPED_BY_WINDOW = ImGuiHoveredFlags_AllowWhenOverlappedByWindow,
		HOVERED_FLAGS_ALLOW_WHEN_DISABLED = ImGuiHoveredFlags_AllowWhenDisabled,
		HOVERED_FLAGS_NO_NAV_OVERRIDE = ImGuiHoveredFlags_NoNavOverride,
		HOVERED_FLAGS_ALLOW_WHEN_OVERLAPPED = ImGuiHoveredFlags_AllowWhenOverlapped,
		HOVERED_FLAGS_RECT_ONLY = ImGuiHoveredFlags_RectOnly,
		HOVERED_FLAGS_ROOT_AND_CHILD_WINDOWS = ImGuiHoveredFlags_RootAndChildWindows,
		HOVERED_FLAGS_FOR_TOOLTIP = ImGuiHoveredFlags_ForTooltip,
		HOVERED_FLAGS_STATIONARY = ImGuiHoveredFlags_Stationary,
		HOVERED_FLAGS_DELAY_NONE = ImGuiHoveredFlags_DelayNone,
		HOVERED_FLAGS_DELAY_SHORT = ImGuiHoveredFlags_DelayShort,
		HOVERED_FLAGS_DELAY_NORMAL = ImGuiHoveredFlags_DelayNormal,
		HOVERED_FLAGS_NO_SHARED_DELAY = ImGuiHoveredFlags_NoSharedDelay,
	};

	enum TabBarFlags {
		TAB_BAR_FLAGS_NONE = ImGuiTabBarFlags_None,
		TAB_BAR_FLAGS_REORDERABLE = ImGuiTabBarFlags_Reorderable,
		TAB_BAR_FLAGS_AUTO_SELECT_NEW_TABS = ImGuiTabBarFlags_AutoSelectNewTabs,
		TAB_BAR_FLAGS_TAB_LIST_POPUP_BUTTON = ImGuiTabBarFlags_TabListPopupButton,
		TAB_BAR_FLAGS_NO_CLOSE_WITH_MIDDLE_MOUSE_BUTTON = ImGuiTabBarFlags_NoCloseWithMiddleMouseButton,
		TAB_BAR_FLAGS_NO_TAB_LIST_SCROLLING_BUTTONS = ImGuiTabBarFlags_NoTabListScrollingButtons,
		TAB_BAR_FLAGS_NO_TOOLTIP = ImGuiTabBarFlags_NoTooltip,
		TAB_BAR_FLAGS_DRAW_SELECTED_OVERLINE = ImGuiTabBarFlags_DrawSelectedOverline,
		TAB_BAR_FLAGS_FITTING_POLICY_MIXED = ImGuiTabBarFlags_FittingPolicyMixed,
		TAB_BAR_FLAGS_FITTING_POLICY_SHRINK = ImGuiTabBarFlags_FittingPolicyShrink,
		TAB_BAR_FLAGS_FITTING_POLICY_SCROLL = ImGuiTabBarFlags_FittingPolicyScroll,
	};

	enum TabItemFlags {
		TAB_ITEM_FLAGS_NONE = ImGuiTabItemFlags_None,
		TAB_ITEM_FLAGS_UNSAVED_DOCUMENT = ImGuiTabItemFlags_UnsavedDocument,
		TAB_ITEM_FLAGS_SET_SELECTED = ImGuiTabItemFlags_SetSelected,
		TAB_ITEM_FLAGS_NO_CLOSE_WITH_MIDDLE_MOUSE_BUTTON = ImGuiTabItemFlags_NoCloseWithMiddleMouseButton,
		TAB_ITEM_FLAGS_NO_PUSH_ID = ImGuiTabItemFlags_NoPushId,
		TAB_ITEM_FLAGS_NO_TOOLTIP = ImGuiTabItemFlags_NoTooltip,
		TAB_ITEM_FLAGS_NO_REORDER = ImGuiTabItemFlags_NoReorder,
		TAB_ITEM_FLAGS_LEADING = ImGuiTabItemFlags_Leading,
		TAB_ITEM_FLAGS_TRAILING = ImGuiTabItemFlags_Trailing,
		TAB_ITEM_FLAGS_NO_ASSUMED_CLOSURE = ImGuiTabItemFlags_NoAssumedClosure,
	};

	enum TableFlags {
		TABLE_FLAGS_NONE = ImGuiTableFlags_None,
		TABLE_FLAGS_RESIZABLE = ImGuiTableFlags_Resizable,
		TABLE_FLAGS_REORDERABLE = ImGuiTableFlags_Reorderable,
		TABLE_FLAGS_HIDEABLE = ImGuiTableFlags_Hideable,
		TABLE_FLAGS_SORTABLE = ImGuiTableFlags_Sortable,
		TABLE_FLAGS_NO_SAVED_SETTINGS = ImGuiTableFlags_NoSavedSettings,
		TABLE_FLAGS_CONTEXT_MENU_IN_BODY = ImGuiTableFlags_ContextMenuInBody,
		TABLE_FLAGS_ROW_BG = ImGuiTableFlags_RowBg,
		TABLE_FLAGS_BORDERS_INNER_H = ImGuiTableFlags_BordersInnerH,
		TABLE_FLAGS_BORDERS_OUTER_H = ImGuiTableFlags_BordersOuterH,
		TABLE_FLAGS_BORDERS_INNER_V = ImGuiTableFlags_BordersInnerV,
		TABLE_FLAGS_BORDERS_OUTER_V = ImGuiTableFlags_BordersOuterV,
		TABLE_FLAGS_BORDERS_H = ImGuiTableFlags_BordersH,
		TABLE_FLAGS_BORDERS_V = ImGuiTableFlags_BordersV,
		TABLE_FLAGS_BORDERS_INNER = ImGuiTableFlags_BordersInner,
		TABLE_FLAGS_BORDERS_OUTER = ImGuiTableFlags_BordersOuter,
		TABLE_FLAGS_BORDERS = ImGuiTableFlags_Borders,
		TABLE_FLAGS_NO_BORDERS_IN_BODY = ImGuiTableFlags_NoBordersInBody,
		TABLE_FLAGS_NO_BORDERS_IN_BODY_UNTIL_RESIZE = ImGuiTableFlags_NoBordersInBodyUntilResize,
		TABLE_FLAGS_SIZING_FIXED_FIT = ImGuiTableFlags_SizingFixedFit,
		TABLE_FLAGS_SIZING_FIXED_SAME = ImGuiTableFlags_SizingFixedSame,
		TABLE_FLAGS_SIZING_STRETCH_PROP = ImGuiTableFlags_SizingStretchProp,
		TABLE_FLAGS_SIZING_STRETCH_SAME = ImGuiTableFlags_SizingStretchSame,
		TABLE_FLAGS_NO_HOST_EXTEND_X = ImGuiTableFlags_NoHostExtendX,
		TABLE_FLAGS_NO_HOST_EXTEND_Y = ImGuiTableFlags_NoHostExtendY,
		TABLE_FLAGS_NO_KEEP_COLUMNS_VISIBLE = ImGuiTableFlags_NoKeepColumnsVisible,
		TABLE_FLAGS_PRECISE_WIDTHS = ImGuiTableFlags_PreciseWidths,
		TABLE_FLAGS_NO_CLIP = ImGuiTableFlags_NoClip,
		TABLE_FLAGS_PAD_OUTER_X = ImGuiTableFlags_PadOuterX,
		TABLE_FLAGS_NO_PAD_OUTER_X = ImGuiTableFlags_NoPadOuterX,
		TABLE_FLAGS_NO_PAD_INNER_X = ImGuiTableFlags_NoPadInnerX,
		TABLE_FLAGS_SCROLL_X = ImGuiTableFlags_ScrollX,
		TABLE_FLAGS_SCROLL_Y = ImGuiTableFlags_ScrollY,
		TABLE_FLAGS_SORT_MULTI = ImGuiTableFlags_SortMulti,
		TABLE_FLAGS_SORT_TRISTATE = ImGuiTableFlags_SortTristate,
		TABLE_FLAGS_HIGHLIGHT_HOVERED_COLUMN = ImGuiTableFlags_HighlightHoveredColumn,
	};

	enum TableColumnFlags {
		TABLE_COLUMN_FLAGS_NONE = ImGuiTableColumnFlags_None,
		TABLE_COLUMN_FLAGS_DISABLED = ImGuiTableColumnFlags_Disabled,
		TABLE_COLUMN_FLAGS_DEFAULT_HIDE = ImGuiTableColumnFlags_DefaultHide,
		TABLE_COLUMN_FLAGS_DEFAULT_SORT = ImGuiTableColumnFlags_DefaultSort,
		TABLE_COLUMN_FLAGS_WIDTH_STRETCH = ImGuiTableColumnFlags_WidthStretch,
		TABLE_COLUMN_FLAGS_WIDTH_FIXED = ImGuiTableColumnFlags_WidthFixed,
		TABLE_COLUMN_FLAGS_NO_RESIZE = ImGuiTableColumnFlags_NoResize,
		TABLE_COLUMN_FLAGS_NO_REORDER = ImGuiTableColumnFlags_NoReorder,
		TABLE_COLUMN_FLAGS_NO_HIDE = ImGuiTableColumnFlags_NoHide,
		TABLE_COLUMN_FLAGS_NO_CLIP = ImGuiTableColumnFlags_NoClip,
		TABLE_COLUMN_FLAGS_NO_SORT = ImGuiTableColumnFlags_NoSort,
		TABLE_COLUMN_FLAGS_NO_SORT_ASCENDING = ImGuiTableColumnFlags_NoSortAscending,
		TABLE_COLUMN_FLAGS_NO_SORT_DESCENDING = ImGuiTableColumnFlags_NoSortDescending,
		TABLE_COLUMN_FLAGS_NO_HEADER_LABEL = ImGuiTableColumnFlags_NoHeaderLabel,
		TABLE_COLUMN_FLAGS_NO_HEADER_WIDTH = ImGuiTableColumnFlags_NoHeaderWidth,
		TABLE_COLUMN_FLAGS_PREFER_SORT_ASCENDING = ImGuiTableColumnFlags_PreferSortAscending,
		TABLE_COLUMN_FLAGS_PREFER_SORT_DESCENDING = ImGuiTableColumnFlags_PreferSortDescending,
		TABLE_COLUMN_FLAGS_INDENT_ENABLE = ImGuiTableColumnFlags_IndentEnable,
		TABLE_COLUMN_FLAGS_INDENT_DISABLE = ImGuiTableColumnFlags_IndentDisable,
		TABLE_COLUMN_FLAGS_ANGLED_HEADER = ImGuiTableColumnFlags_AngledHeader,
	};

	enum DockNodeFlags {
		DOCK_NODE_FLAGS_NONE = ImGuiDockNodeFlags_None,
		DOCK_NODE_FLAGS_KEEP_ALIVE_ONLY = ImGuiDockNodeFlags_KeepAliveOnly,
		DOCK_NODE_FLAGS_NO_DOCKING_OVER_CENTRAL_NODE = ImGuiDockNodeFlags_NoDockingOverCentralNode,
		DOCK_NODE_FLAGS_PASSTHRU_CENTRAL_NODE = ImGuiDockNodeFlags_PassthruCentralNode,
		DOCK_NODE_FLAGS_NO_DOCKING_SPLIT = ImGuiDockNodeFlags_NoDockingSplit,
		DOCK_NODE_FLAGS_NO_RESIZE = ImGuiDockNodeFlags_NoResize,
		DOCK_NODE_FLAGS_AUTO_HIDE_TAB_BAR = ImGuiDockNodeFlags_AutoHideTabBar,
		DOCK_NODE_FLAGS_NO_UNDOCKING = ImGuiDockNodeFlags_NoUndocking,
	};

	// --- Regular Enums ---

	enum Cond {
		COND_NONE = ImGuiCond_None,
		COND_ALWAYS = ImGuiCond_Always,
		COND_ONCE = ImGuiCond_Once,
		COND_FIRST_USE_EVER = ImGuiCond_FirstUseEver,
		COND_APPEARING = ImGuiCond_Appearing,
	};

	enum Dir {
		DIR_NONE = ImGuiDir_None,
		DIR_LEFT = ImGuiDir_Left,
		DIR_RIGHT = ImGuiDir_Right,
		DIR_UP = ImGuiDir_Up,
		DIR_DOWN = ImGuiDir_Down,
	};

	enum MouseButton {
		MOUSE_BUTTON_LEFT = ImGuiMouseButton_Left,
		MOUSE_BUTTON_RIGHT = ImGuiMouseButton_Right,
		MOUSE_BUTTON_MIDDLE = ImGuiMouseButton_Middle,
		MOUSE_BUTTON_WHEEL_UP = 4,
		MOUSE_BUTTON_WHEEL_DOWN = 5,
	};

	enum StyleColor {
		STYLE_COLOR_TEXT = ImGuiCol_Text,
		STYLE_COLOR_TEXT_DISABLED = ImGuiCol_TextDisabled,
		STYLE_COLOR_WINDOW_BG = ImGuiCol_WindowBg,
		STYLE_COLOR_CHILD_BG = ImGuiCol_ChildBg,
		STYLE_COLOR_POPUP_BG = ImGuiCol_PopupBg,
		STYLE_COLOR_BORDER = ImGuiCol_Border,
		STYLE_COLOR_BORDER_SHADOW = ImGuiCol_BorderShadow,
		STYLE_COLOR_FRAME_BG = ImGuiCol_FrameBg,
		STYLE_COLOR_FRAME_BG_HOVERED = ImGuiCol_FrameBgHovered,
		STYLE_COLOR_FRAME_BG_ACTIVE = ImGuiCol_FrameBgActive,
		STYLE_COLOR_TITLE_BG = ImGuiCol_TitleBg,
		STYLE_COLOR_TITLE_BG_ACTIVE = ImGuiCol_TitleBgActive,
		STYLE_COLOR_TITLE_BG_COLLAPSED = ImGuiCol_TitleBgCollapsed,
		STYLE_COLOR_MENU_BAR_BG = ImGuiCol_MenuBarBg,
		STYLE_COLOR_SCROLLBAR_BG = ImGuiCol_ScrollbarBg,
		STYLE_COLOR_SCROLLBAR_GRAB = ImGuiCol_ScrollbarGrab,
		STYLE_COLOR_SCROLLBAR_GRAB_HOVERED = ImGuiCol_ScrollbarGrabHovered,
		STYLE_COLOR_SCROLLBAR_GRAB_ACTIVE = ImGuiCol_ScrollbarGrabActive,
		STYLE_COLOR_CHECK_MARK = ImGuiCol_CheckMark,
		STYLE_COLOR_SLIDER_GRAB = ImGuiCol_SliderGrab,
		STYLE_COLOR_SLIDER_GRAB_ACTIVE = ImGuiCol_SliderGrabActive,
		STYLE_COLOR_BUTTON = ImGuiCol_Button,
		STYLE_COLOR_BUTTON_HOVERED = ImGuiCol_ButtonHovered,
		STYLE_COLOR_BUTTON_ACTIVE = ImGuiCol_ButtonActive,
		STYLE_COLOR_HEADER = ImGuiCol_Header,
		STYLE_COLOR_HEADER_HOVERED = ImGuiCol_HeaderHovered,
		STYLE_COLOR_HEADER_ACTIVE = ImGuiCol_HeaderActive,
		STYLE_COLOR_SEPARATOR = ImGuiCol_Separator,
		STYLE_COLOR_SEPARATOR_HOVERED = ImGuiCol_SeparatorHovered,
		STYLE_COLOR_SEPARATOR_ACTIVE = ImGuiCol_SeparatorActive,
		STYLE_COLOR_RESIZE_GRIP = ImGuiCol_ResizeGrip,
		STYLE_COLOR_RESIZE_GRIP_HOVERED = ImGuiCol_ResizeGripHovered,
		STYLE_COLOR_RESIZE_GRIP_ACTIVE = ImGuiCol_ResizeGripActive,
		STYLE_COLOR_INPUT_TEXT_CURSOR = ImGuiCol_InputTextCursor,
		STYLE_COLOR_TAB_HOVERED = ImGuiCol_TabHovered,
		STYLE_COLOR_TAB = ImGuiCol_Tab,
		STYLE_COLOR_TAB_SELECTED = ImGuiCol_TabSelected,
		STYLE_COLOR_TAB_SELECTED_OVERLINE = ImGuiCol_TabSelectedOverline,
		STYLE_COLOR_TAB_DIMMED = ImGuiCol_TabDimmed,
		STYLE_COLOR_TAB_DIMMED_SELECTED = ImGuiCol_TabDimmedSelected,
		STYLE_COLOR_TAB_DIMMED_SELECTED_OVERLINE = ImGuiCol_TabDimmedSelectedOverline,
		STYLE_COLOR_DOCKING_PREVIEW = ImGuiCol_DockingPreview,
		STYLE_COLOR_DOCKING_EMPTY_BG = ImGuiCol_DockingEmptyBg,
		STYLE_COLOR_PLOT_LINES = ImGuiCol_PlotLines,
		STYLE_COLOR_PLOT_LINES_HOVERED = ImGuiCol_PlotLinesHovered,
		STYLE_COLOR_PLOT_HISTOGRAM = ImGuiCol_PlotHistogram,
		STYLE_COLOR_PLOT_HISTOGRAM_HOVERED = ImGuiCol_PlotHistogramHovered,
		STYLE_COLOR_TABLE_HEADER_BG = ImGuiCol_TableHeaderBg,
		STYLE_COLOR_TABLE_BORDER_STRONG = ImGuiCol_TableBorderStrong,
		STYLE_COLOR_TABLE_BORDER_LIGHT = ImGuiCol_TableBorderLight,
		STYLE_COLOR_TABLE_ROW_BG = ImGuiCol_TableRowBg,
		STYLE_COLOR_TABLE_ROW_BG_ALT = ImGuiCol_TableRowBgAlt,
		STYLE_COLOR_TEXT_LINK = ImGuiCol_TextLink,
		STYLE_COLOR_TEXT_SELECTED_BG = ImGuiCol_TextSelectedBg,
		STYLE_COLOR_TREE_LINES = ImGuiCol_TreeLines,
		STYLE_COLOR_DRAG_DROP_TARGET = ImGuiCol_DragDropTarget,
		STYLE_COLOR_DRAG_DROP_TARGET_BG = ImGuiCol_DragDropTargetBg,
		STYLE_COLOR_UNSAVED_MARKER = ImGuiCol_UnsavedMarker,
		STYLE_COLOR_NAV_CURSOR = ImGuiCol_NavCursor,
		STYLE_COLOR_NAV_WINDOWING_HIGHLIGHT = ImGuiCol_NavWindowingHighlight,
		STYLE_COLOR_NAV_WINDOWING_DIM_BG = ImGuiCol_NavWindowingDimBg,
		STYLE_COLOR_MODAL_WINDOW_DIM_BG = ImGuiCol_ModalWindowDimBg,
	};

	enum StyleVar {
		STYLE_VAR_ALPHA = ImGuiStyleVar_Alpha,
		STYLE_VAR_DISABLED_ALPHA = ImGuiStyleVar_DisabledAlpha,
		STYLE_VAR_WINDOW_PADDING = ImGuiStyleVar_WindowPadding,
		STYLE_VAR_WINDOW_ROUNDING = ImGuiStyleVar_WindowRounding,
		STYLE_VAR_WINDOW_BORDER_SIZE = ImGuiStyleVar_WindowBorderSize,
		STYLE_VAR_WINDOW_MIN_SIZE = ImGuiStyleVar_WindowMinSize,
		STYLE_VAR_WINDOW_TITLE_ALIGN = ImGuiStyleVar_WindowTitleAlign,
		STYLE_VAR_CHILD_ROUNDING = ImGuiStyleVar_ChildRounding,
		STYLE_VAR_CHILD_BORDER_SIZE = ImGuiStyleVar_ChildBorderSize,
		STYLE_VAR_POPUP_ROUNDING = ImGuiStyleVar_PopupRounding,
		STYLE_VAR_POPUP_BORDER_SIZE = ImGuiStyleVar_PopupBorderSize,
		STYLE_VAR_FRAME_PADDING = ImGuiStyleVar_FramePadding,
		STYLE_VAR_FRAME_ROUNDING = ImGuiStyleVar_FrameRounding,
		STYLE_VAR_FRAME_BORDER_SIZE = ImGuiStyleVar_FrameBorderSize,
		STYLE_VAR_ITEM_SPACING = ImGuiStyleVar_ItemSpacing,
		STYLE_VAR_ITEM_INNER_SPACING = ImGuiStyleVar_ItemInnerSpacing,
		STYLE_VAR_INDENT_SPACING = ImGuiStyleVar_IndentSpacing,
		STYLE_VAR_CELL_PADDING = ImGuiStyleVar_CellPadding,
		STYLE_VAR_SCROLLBAR_SIZE = ImGuiStyleVar_ScrollbarSize,
		STYLE_VAR_SCROLLBAR_ROUNDING = ImGuiStyleVar_ScrollbarRounding,
		STYLE_VAR_SCROLLBAR_PADDING = ImGuiStyleVar_ScrollbarPadding,
		STYLE_VAR_GRAB_MIN_SIZE = ImGuiStyleVar_GrabMinSize,
		STYLE_VAR_GRAB_ROUNDING = ImGuiStyleVar_GrabRounding,
		STYLE_VAR_IMAGE_ROUNDING = ImGuiStyleVar_ImageRounding,
		STYLE_VAR_IMAGE_BORDER_SIZE = ImGuiStyleVar_ImageBorderSize,
		STYLE_VAR_TAB_ROUNDING = ImGuiStyleVar_TabRounding,
		STYLE_VAR_TAB_BORDER_SIZE = ImGuiStyleVar_TabBorderSize,
		STYLE_VAR_TAB_MIN_WIDTH_BASE = ImGuiStyleVar_TabMinWidthBase,
		STYLE_VAR_TAB_MIN_WIDTH_SHRINK = ImGuiStyleVar_TabMinWidthShrink,
		STYLE_VAR_TAB_BAR_BORDER_SIZE = ImGuiStyleVar_TabBarBorderSize,
		STYLE_VAR_TAB_BAR_OVERLINE_SIZE = ImGuiStyleVar_TabBarOverlineSize,
		STYLE_VAR_TABLE_ANGLED_HEADERS_ANGLE = ImGuiStyleVar_TableAngledHeadersAngle,
		STYLE_VAR_TABLE_ANGLED_HEADERS_TEXT_ALIGN = ImGuiStyleVar_TableAngledHeadersTextAlign,
		STYLE_VAR_TREE_LINES_SIZE = ImGuiStyleVar_TreeLinesSize,
		STYLE_VAR_TREE_LINES_ROUNDING = ImGuiStyleVar_TreeLinesRounding,
		STYLE_VAR_BUTTON_TEXT_ALIGN = ImGuiStyleVar_ButtonTextAlign,
		STYLE_VAR_SELECTABLE_TEXT_ALIGN = ImGuiStyleVar_SelectableTextAlign,
		STYLE_VAR_SEPARATOR_SIZE = ImGuiStyleVar_SeparatorSize,
		STYLE_VAR_SEPARATOR_TEXT_BORDER_SIZE = ImGuiStyleVar_SeparatorTextBorderSize,
		STYLE_VAR_SEPARATOR_TEXT_ALIGN = ImGuiStyleVar_SeparatorTextAlign,
		STYLE_VAR_SEPARATOR_TEXT_PADDING = ImGuiStyleVar_SeparatorTextPadding,
		STYLE_VAR_DOCKING_SEPARATOR_SIZE = ImGuiStyleVar_DockingSeparatorSize,
	};

	// --- Node Editor Enums ---

	enum NodeEditorPinKind {
		NODE_EDITOR_PIN_KIND_INPUT = (int)ax::NodeEditor::PinKind::Input,
		NODE_EDITOR_PIN_KIND_OUTPUT = (int)ax::NodeEditor::PinKind::Output,
	};

	enum NodeEditorFlowDirection {
		NODE_EDITOR_FLOW_DIRECTION_FORWARD = (int)ax::NodeEditor::FlowDirection::Forward,
		NODE_EDITOR_FLOW_DIRECTION_BACKWARD = (int)ax::NodeEditor::FlowDirection::Backward,
	};

	enum NodeEditorStyleColor {
		NODE_EDITOR_STYLE_COLOR_BG = ax::NodeEditor::StyleColor_Bg,
		NODE_EDITOR_STYLE_COLOR_GRID = ax::NodeEditor::StyleColor_Grid,
		NODE_EDITOR_STYLE_COLOR_NODE_BG = ax::NodeEditor::StyleColor_NodeBg,
		NODE_EDITOR_STYLE_COLOR_NODE_BORDER = ax::NodeEditor::StyleColor_NodeBorder,
		NODE_EDITOR_STYLE_COLOR_HOV_NODE_BORDER = ax::NodeEditor::StyleColor_HovNodeBorder,
		NODE_EDITOR_STYLE_COLOR_SEL_NODE_BORDER = ax::NodeEditor::StyleColor_SelNodeBorder,
		NODE_EDITOR_STYLE_COLOR_NODE_SEL_RECT = ax::NodeEditor::StyleColor_NodeSelRect,
		NODE_EDITOR_STYLE_COLOR_NODE_SEL_RECT_BORDER = ax::NodeEditor::StyleColor_NodeSelRectBorder,
		NODE_EDITOR_STYLE_COLOR_HOV_LINK_BORDER = ax::NodeEditor::StyleColor_HovLinkBorder,
		NODE_EDITOR_STYLE_COLOR_SEL_LINK_BORDER = ax::NodeEditor::StyleColor_SelLinkBorder,
		NODE_EDITOR_STYLE_COLOR_HIGHLIGHT_LINK_BORDER = ax::NodeEditor::StyleColor_HighlightLinkBorder,
		NODE_EDITOR_STYLE_COLOR_LINK_SEL_RECT = ax::NodeEditor::StyleColor_LinkSelRect,
		NODE_EDITOR_STYLE_COLOR_LINK_SEL_RECT_BORDER = ax::NodeEditor::StyleColor_LinkSelRectBorder,
		NODE_EDITOR_STYLE_COLOR_PIN_RECT = ax::NodeEditor::StyleColor_PinRect,
		NODE_EDITOR_STYLE_COLOR_PIN_RECT_BORDER = ax::NodeEditor::StyleColor_PinRectBorder,
		NODE_EDITOR_STYLE_COLOR_FLOW = ax::NodeEditor::StyleColor_Flow,
		NODE_EDITOR_STYLE_COLOR_FLOW_MARKER = ax::NodeEditor::StyleColor_FlowMarker,
		NODE_EDITOR_STYLE_COLOR_GROUP_BG = ax::NodeEditor::StyleColor_GroupBg,
		NODE_EDITOR_STYLE_COLOR_GROUP_BORDER = ax::NodeEditor::StyleColor_GroupBorder,
	};

	enum NodeEditorStyleVar {
		NODE_EDITOR_STYLE_VAR_NODE_PADDING = ax::NodeEditor::StyleVar_NodePadding,
		NODE_EDITOR_STYLE_VAR_NODE_ROUNDING = ax::NodeEditor::StyleVar_NodeRounding,
		NODE_EDITOR_STYLE_VAR_NODE_BORDER_WIDTH = ax::NodeEditor::StyleVar_NodeBorderWidth,
		NODE_EDITOR_STYLE_VAR_HOVERED_NODE_BORDER_WIDTH = ax::NodeEditor::StyleVar_HoveredNodeBorderWidth,
		NODE_EDITOR_STYLE_VAR_SELECTED_NODE_BORDER_WIDTH = ax::NodeEditor::StyleVar_SelectedNodeBorderWidth,
		NODE_EDITOR_STYLE_VAR_PIN_ROUNDING = ax::NodeEditor::StyleVar_PinRounding,
		NODE_EDITOR_STYLE_VAR_PIN_BORDER_WIDTH = ax::NodeEditor::StyleVar_PinBorderWidth,
		NODE_EDITOR_STYLE_VAR_LINK_STRENGTH = ax::NodeEditor::StyleVar_LinkStrength,
		NODE_EDITOR_STYLE_VAR_SOURCE_DIRECTION = ax::NodeEditor::StyleVar_SourceDirection,
		NODE_EDITOR_STYLE_VAR_TARGET_DIRECTION = ax::NodeEditor::StyleVar_TargetDirection,
		NODE_EDITOR_STYLE_VAR_SCROLL_DURATION = ax::NodeEditor::StyleVar_ScrollDuration,
		NODE_EDITOR_STYLE_VAR_FLOW_MARKER_DISTANCE = ax::NodeEditor::StyleVar_FlowMarkerDistance,
		NODE_EDITOR_STYLE_VAR_FLOW_SPEED = ax::NodeEditor::StyleVar_FlowSpeed,
		NODE_EDITOR_STYLE_VAR_FLOW_DURATION = ax::NodeEditor::StyleVar_FlowDuration,
		NODE_EDITOR_STYLE_VAR_PIVOT_ALIGNMENT = ax::NodeEditor::StyleVar_PivotAlignment,
		NODE_EDITOR_STYLE_VAR_PIVOT_SIZE = ax::NodeEditor::StyleVar_PivotSize,
		NODE_EDITOR_STYLE_VAR_PIVOT_SCALE = ax::NodeEditor::StyleVar_PivotScale,
		NODE_EDITOR_STYLE_VAR_PIN_CORNERS = ax::NodeEditor::StyleVar_PinCorners,
		NODE_EDITOR_STYLE_VAR_PIN_RADIUS = ax::NodeEditor::StyleVar_PinRadius,
		NODE_EDITOR_STYLE_VAR_PIN_ARROW_SIZE = ax::NodeEditor::StyleVar_PinArrowSize,
		NODE_EDITOR_STYLE_VAR_PIN_ARROW_WIDTH = ax::NodeEditor::StyleVar_PinArrowWidth,
		NODE_EDITOR_STYLE_VAR_GROUP_ROUNDING = ax::NodeEditor::StyleVar_GroupRounding,
		NODE_EDITOR_STYLE_VAR_GROUP_BORDER_WIDTH = ax::NodeEditor::StyleVar_GroupBorderWidth,
		NODE_EDITOR_STYLE_VAR_HIGHLIGHT_CONNECTED_LINKS = ax::NodeEditor::StyleVar_HighlightConnectedLinks,
		NODE_EDITOR_STYLE_VAR_SNAP_LINK_TO_PIN_DIR = ax::NodeEditor::StyleVar_SnapLinkToPinDir,
		NODE_EDITOR_STYLE_VAR_HOVERED_NODE_BORDER_OFFSET = ax::NodeEditor::StyleVar_HoveredNodeBorderOffset,
		NODE_EDITOR_STYLE_VAR_SELECTED_NODE_BORDER_OFFSET = ax::NodeEditor::StyleVar_SelectedNodeBorderOffset,
	};

	// =========================================================================
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
	Vector2 calc_text_size(const String &text);

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
	void node_editor_set_group_size(int64_t id, const Vector2 &size);
	void node_editor_center_node_on_screen(int64_t id);
	void node_editor_group(const Vector2 &size);

	// Node Editor - Pins
	void node_editor_begin_pin(int64_t id, int kind);
	void node_editor_end_pin();
	void node_editor_pin_rect(const Vector2 &a, const Vector2 &b);
	void node_editor_pin_pivot_rect(const Vector2 &a, const Vector2 &b);
	void node_editor_pin_pivot_alignment(const Vector2 &alignment);
	void node_editor_pin_pivot_size(const Vector2 &size);
	void node_editor_pin_pivot_scale(const Vector2 &scale);

	// Node Editor - Links
	bool node_editor_link(int64_t id, int64_t start_pin_id, int64_t end_pin_id, const Color &color = Color(1, 1, 1, 1), float thickness = 1.0f);
	bool node_editor_delete_link(int64_t id);
	void node_editor_flow(int64_t link_id, int direction = 0);
	Array node_editor_get_link_pins(int64_t link_id);
	bool node_editor_pin_had_any_links(int64_t pin_id);
	bool node_editor_has_any_links_node(int64_t node_id);
	bool node_editor_has_any_links_pin(int64_t pin_id);
	int node_editor_break_links_node(int64_t node_id);
	int node_editor_break_links_pin(int64_t pin_id);

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
	bool node_editor_has_selection_changed();
	int node_editor_get_selected_object_count();
	int node_editor_get_selected_node_count();
	PackedInt64Array node_editor_get_selected_nodes(int max_count = 256);
	PackedInt64Array node_editor_get_selected_links(int max_count = 256);
	bool node_editor_is_node_selected(int64_t id);
	bool node_editor_is_link_selected(int64_t id);
	void node_editor_select_node(int64_t id, bool append = false);
	void node_editor_select_link(int64_t id, bool append = false);
	void node_editor_deselect_node(int64_t id);
	void node_editor_deselect_link(int64_t id);
	void node_editor_clear_selection();

	// Node Editor - Hover / Click
	int64_t node_editor_get_hovered_node();
	int64_t node_editor_get_hovered_pin();
	int64_t node_editor_get_hovered_link();
	int64_t node_editor_get_double_clicked_node();
	int64_t node_editor_get_double_clicked_pin();
	int64_t node_editor_get_double_clicked_link();
	bool node_editor_is_background_clicked();
	bool node_editor_is_background_double_clicked();
	bool node_editor_show_background_context_menu();
	Array node_editor_show_node_context_menu();
	Array node_editor_show_pin_context_menu();
	Array node_editor_show_link_context_menu();

	// Node Editor - Navigation
	void node_editor_navigate_to_content(float duration = -1.0f);
	void node_editor_navigate_to_selection(bool zoom_in = false, float duration = -1.0f);
	float node_editor_get_current_zoom();

	// Node Editor - Shortcuts
	void node_editor_enable_shortcuts(bool enable);
	bool node_editor_are_shortcuts_enabled();
	bool node_editor_begin_shortcut();
	bool node_editor_accept_cut();
	bool node_editor_accept_copy();
	bool node_editor_accept_paste();
	bool node_editor_accept_duplicate();
	bool node_editor_accept_create_node();
	int node_editor_get_action_context_size();
	PackedInt64Array node_editor_get_action_context_nodes(int max_count = 256);
	PackedInt64Array node_editor_get_action_context_links(int max_count = 256);
	void node_editor_end_shortcut();

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
	int64_t node_editor_get_node_background_draw_list(int64_t node_id);
	int64_t node_editor_get_hint_foreground_draw_list();
	int64_t node_editor_get_hint_background_draw_list();

	// ImDrawList - Primitives
	void draw_list_add_line(int64_t draw_list, const Vector2 &p1, const Vector2 &p2, const Color &color, float thickness = 1.0f);
	void draw_list_add_rect(int64_t draw_list, const Vector2 &p_min, const Vector2 &p_max, const Color &color, float rounding = 0.0f, int flags = 0, float thickness = 1.0f);
	void draw_list_add_rect_filled(int64_t draw_list, const Vector2 &p_min, const Vector2 &p_max, const Color &color, float rounding = 0.0f, int flags = 0);
	void draw_list_add_circle(int64_t draw_list, const Vector2 &center, float radius, const Color &color, int segments = 0, float thickness = 1.0f);
	void draw_list_add_circle_filled(int64_t draw_list, const Vector2 &center, float radius, const Color &color, int segments = 0);
	void draw_list_add_triangle(int64_t draw_list, const Vector2 &p1, const Vector2 &p2, const Vector2 &p3, const Color &color, float thickness = 1.0f);
	void draw_list_add_triangle_filled(int64_t draw_list, const Vector2 &p1, const Vector2 &p2, const Vector2 &p3, const Color &color);
	void draw_list_add_text(int64_t draw_list, const Vector2 &pos, const Color &color, const String &text);
	void draw_list_add_bezier_cubic(int64_t draw_list, const Vector2 &p1, const Vector2 &p2, const Vector2 &p3, const Vector2 &p4, const Color &color, float thickness = 1.0f, int segments = 0);
	void draw_list_add_bezier_quadratic(int64_t draw_list, const Vector2 &p1, const Vector2 &p2, const Vector2 &p3, const Color &color, float thickness = 1.0f, int segments = 0);

	// ImDrawList - Path
	void draw_list_path_clear(int64_t draw_list);
	void draw_list_path_line_to(int64_t draw_list, const Vector2 &pos);
	void draw_list_path_stroke(int64_t draw_list, const Color &color, int flags = 0, float thickness = 1.0f);
	void draw_list_path_fill_convex(int64_t draw_list, const Color &color);
	void draw_list_path_arc_to(int64_t draw_list, const Vector2 &center, float radius, float a_min, float a_max, int segments = 0);
	void draw_list_path_rect(int64_t draw_list, const Vector2 &rect_min, const Vector2 &rect_max, float rounding = 0.0f, int flags = 0);

	// ImDrawList - Channels
	void draw_list_channels_split(int64_t draw_list, int count);
	void draw_list_channels_set_current(int64_t draw_list, int channel_index);
	void draw_list_channels_merge(int64_t draw_list);

	// Font configuration
	void set_chinese_font_path(const String &path);
	void set_font_size(float size);

	// Internal - not exposed to GDScript
	ImGuiContext *get_context_internal() { return imgui_context; }
};

} // namespace godot

// =============================================================================
// VARIANT_ENUM_CAST / VARIANT_BITFIELD_CAST Registrations
// =============================================================================

// Bitfield flags
VARIANT_BITFIELD_CAST(godot::ImGuiGodot::WindowFlags);
VARIANT_BITFIELD_CAST(godot::ImGuiGodot::ChildFlags);
VARIANT_BITFIELD_CAST(godot::ImGuiGodot::ColorEditFlags);
VARIANT_BITFIELD_CAST(godot::ImGuiGodot::ComboFlags);
VARIANT_BITFIELD_CAST(godot::ImGuiGodot::TreeNodeFlags);
VARIANT_BITFIELD_CAST(godot::ImGuiGodot::PopupFlags);
VARIANT_BITFIELD_CAST(godot::ImGuiGodot::FocusedFlags);
VARIANT_BITFIELD_CAST(godot::ImGuiGodot::HoveredFlags);
VARIANT_BITFIELD_CAST(godot::ImGuiGodot::TabBarFlags);
VARIANT_BITFIELD_CAST(godot::ImGuiGodot::TabItemFlags);
VARIANT_BITFIELD_CAST(godot::ImGuiGodot::TableFlags);
VARIANT_BITFIELD_CAST(godot::ImGuiGodot::TableColumnFlags);
VARIANT_BITFIELD_CAST(godot::ImGuiGodot::DockNodeFlags);

// Regular enums
VARIANT_ENUM_CAST(godot::ImGuiGodot::Cond);
VARIANT_ENUM_CAST(godot::ImGuiGodot::Dir);
VARIANT_ENUM_CAST(godot::ImGuiGodot::MouseButton);
VARIANT_ENUM_CAST(godot::ImGuiGodot::StyleColor);
VARIANT_ENUM_CAST(godot::ImGuiGodot::StyleVar);
VARIANT_ENUM_CAST(godot::ImGuiGodot::NodeEditorPinKind);
VARIANT_ENUM_CAST(godot::ImGuiGodot::NodeEditorFlowDirection);
VARIANT_ENUM_CAST(godot::ImGuiGodot::NodeEditorStyleColor);
VARIANT_ENUM_CAST(godot::ImGuiGodot::NodeEditorStyleVar);

#endif // IMGUI_GODOT_H
