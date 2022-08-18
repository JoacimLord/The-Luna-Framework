#pragma once

//APPLICATION
#include "LfwAPI/Core/Application.h"

//CORE
#include "LfwAPI/Core/Defines.h"
#include "LfwAPI/Core/DeltaTime.h"

//WINDOW-ABSTRACTION
#include "LfwAPI/Core/Window.h"
#include "LfwAPI/Core/WindowLogic.h"

//RENDERER
#include "LfwAPI/Renderer/Shader.h"
#include "LfwAPI/Renderer/Buffers.h"
#include "LfwAPI/Renderer/Texture.h"
#include "LfwAPI/Renderer/VertexArray.h"
#include "LfwAPI/Renderer/Renderer.h"
#include "LfwAPI/Renderer/Framebuffer.h"
#include "LfwAPI/Renderer/Colors.h"

//GRAPHICS
#include "LfwAPI/Utility/Debug.h"
#include "LfwAPI/Graphics/Sprite.h"

//KEYCODES
#include "LfwAPI/Core/KeyCodes.h"
#include "LfwAPI/Core/MouseCodes.h"
#include "LfwAPI/Core/Input.h"

//GUI
#include "LfwAPI/UI/UI.h"

//EVENTS
#include "LfwAPI/EventHandler/MainEventBaseClass.h"

//KEYS
#include "LfwAPI/EventHandler/KeyEvents/KeyButtonBaseEvent.h"
#include "LfwAPI/EventHandler/KeyEvents/KeyPressed.h"
#include "LfwAPI/EventHandler/KeyEvents/KeyReleased.h"
#include "LfwAPI/EventHandler/KeyEvents/KeyTyped.h"

//MOUSE
#include "LfwAPI/EventHandler/MouseEvents/MouseButtonBaseEvent.h"
#include "LfwAPI/EventHandler/MouseEvents/MouseButtonPressed.h"
#include "LfwAPI/EventHandler/MouseEvents/MouseButtonReleased.h"
#include "LfwAPI/EventHandler/MouseEvents/MouseMove.h"
#include "LfwAPI/EventHandler/MouseEvents/MouseWheelScroll.h"

//WINDOW			
#include "LfwAPI/EventHandler/WindowEvents/WindowClose.h"
#include "LfwAPI/EventHandler/WindowEvents/WindowResize.h"

//CLOCK
#include "LfwAPI/Core/Clock.h"

//MATH
#include "LfwAPI/Maths/Mathf.h"

//VECTORS
#include "LfwAPI/Maths/Vec2.h"
#include "LfwAPI/Maths/Vec3.h"
#include "LfwAPI/Maths/Vec4.h"

//DEBUG
//#include "LunaAPI/Utility/Debug.h"

//AUDIOENGINE
#include "LfwAPI/Audio/AudioEngine/AudioEngine.h"
