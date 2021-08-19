#pragma once

#include "pch.h"
#include <tinyxml2.h>
#include "Log.h"

namespace fr {
	class Reader {
	public:
		Reader() = default;
		~Reader() {
			_Document.Clear();
		}

		void Close() {
			_Document.Clear();
		}

		void Open(const char* filename) {
			_Document.LoadFile(filename);
			if (_Document.Error()) {
				String log = _Document.ErrorStr();
				ERROR(log);
				return;
			}
		}

		tinyxml2::XMLElement* Root() {
			return _Document.RootElement();
		}

		std::vector<XMLElement*> ChildElements(XMLElement* el = nullptr) {
			std::vector<tinyxml2::XMLElement*> children;

			if (el == nullptr) {
				for (tinyxml2::XMLElement* e = _Document.FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
					children.push_back(e);
				}
			}
			else {
				for (tinyxml2::XMLElement* e = el->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
					children.push_back(e);
				}
			}
			return children;
		}

		int GetInt(tinyxml2::XMLElement* e) {
			ASSERT(e && "Invalid XML-Element!");
			return e->IntAttribute("value");
		}

		int GetIntAttr(const char* name, tinyxml2::XMLElement* e) {
			ASSERT(e && "Invalid XML-Element!");
			return e->IntAttribute(name);
		}

		float GetFloat(tinyxml2::XMLElement* e) {
			ASSERT(e && "Invalid XML-Element!");
			return e->FloatAttribute("value");
		}

		float GetFloatAttr(const char* name, tinyxml2::XMLElement* e) {
			ASSERT(e && "Invalid XML-Element!");
			return e->FloatAttribute(name);
		}

		const std::string& GetString(tinyxml2::XMLElement* e) {
			ASSERT(e && "Invalid XML-Element!");
			return e->Attribute("value");
		}

		const std::string& GetStringAttr(const char* name, tinyxml2::XMLElement* e) {
			ASSERT(e && "Invalid XML-Element!");
			return e->Attribute(name);
		}

		const Vec3& GetVec3(tinyxml2::XMLElement* e) {
			ASSERT(e && "Invalid XML-Element!");
			float x = e->FloatAttribute("x");
			float y = e->FloatAttribute("y");
			float z = e->FloatAttribute("z");
			return Vec3(x, y, z);
		}

		const Vec3& GetColor3(tinyxml2::XMLElement* e) {
			ASSERT(e && "Invalid XML-Element!");
			float r = e->FloatAttribute("r");
			float g = e->FloatAttribute("g");
			float b = e->FloatAttribute("b");
			return Vec3(r, g, b);
		}

		const Vec4& GetColor4(tinyxml2::XMLElement* e) {
			ASSERT(e && "Invalid XML-Element!");
			float r = e->FloatAttribute("r");
			float g = e->FloatAttribute("g");
			float b = e->FloatAttribute("b");
			float a = e->FloatAttribute("a");
			return Vec4(r, g, b, a);
		}

	private:
		tinyxml2::XMLDocument _Document;
	};

	class Writer {
	public:
		Writer() : _PushedTagCount(0), _FILE(nullptr), _Printer(nullptr) {}
		~Writer() { INFO("Writer Destroyed!"); }

		void Open(const char* filename) {
			_FILE = fopen(filename, "w+");
			_Printer = new tinyxml2::XMLPrinter(_FILE);
			_Printer->PushHeader(true, true);
		}

		void Close(bool compact = false) {
			tinyxml2::XMLDocument document;
			document.Parse(_Printer->CStr());

			if (_FILE != nullptr) {
				fclose(_FILE);
				_Printer->ClearBuffer();
			}
			ASSERT(_PushedTagCount == 0 && "XML-Tag not closed!");
		}

		void PushTag(const char* name) {
			_Printer->OpenElement(name);
			++_PushedTagCount;
		}

		void PopTag() {
			ASSERT(_PushedTagCount > 0 && "XML-Tag not closed!");
			_Printer->CloseElement();
			--_PushedTagCount;
		}


		// serialize int
		void PushIntAttr(const char* name, int value) {
			_Printer->PushAttribute(name, value);
		}

		void PushFloatAttr(const char* name, float value) {
			_Printer->PushAttribute(name, value);
		}

		void PushStringAttr(const char* name, const char* value) {
			_Printer->PushAttribute(name, value);
		}

		// ------------------------------------------------------

		// serialize int
		void PushInt(const char* tagName, int value) {
			_Printer->OpenElement(tagName);
			_Printer->PushAttribute("value", value);
			_Printer->CloseElement(true);
		}

		// serialize int
		void PushFloat(const char* tagName, float value) {
			_Printer->OpenElement(tagName);
			_Printer->PushAttribute("value", value);
			_Printer->CloseElement(true);
		}

		// serialize int
		void PushString(const char* tagName, const char* value) {
			_Printer->OpenElement(tagName);
			_Printer->PushAttribute("value", value);
			_Printer->CloseElement(true);
		}

		// serialize vector3
		void PushVec3(const char* tagName, const Vec3& v) {
			_Printer->OpenElement(tagName);
			_Printer->PushAttribute("x", v.x);
			_Printer->PushAttribute("y", v.y);
			_Printer->PushAttribute("z", v.z);
			_Printer->CloseElement(true);
		}

		// serialize vector3
		void PushColor3(const char* tagName, const Vec3& c) {
			_Printer->OpenElement(tagName);
			_Printer->PushAttribute("r", c.x);
			_Printer->PushAttribute("g", c.y);
			_Printer->PushAttribute("b", c.z);
			_Printer->CloseElement(true);
		}

		// serialize color4
		void PushColor4(const char* tagName, const Vec4& c) {
			_Printer->OpenElement(tagName);
			_Printer->PushAttribute("r", c.x);
			_Printer->PushAttribute("g", c.y);
			_Printer->PushAttribute("b", c.z);
			_Printer->PushAttribute("a", c.w);
			_Printer->CloseElement(true);
		}

	private:
		FILE* _FILE;
		FRuint _PushedTagCount;
		tinyxml2::XMLPrinter* _Printer;
	};
}