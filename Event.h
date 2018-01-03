#pragma once
#include <iostream>
#include <vector>

enum MessageType {
	MSG_UNKNOWN = 0,
	MSG_KEYBOARD,
	MSG_MOUSE,
	MSG_MOUSE_SCROLL,
};

class Message {
public:
	MessageType m_Type;
	int m_Id;
	Message(MessageType type, int id) : m_Type(type), m_Id(id) {}
};

class MouseMessage : public Message {
public:
	MouseMessage(int id) : Message(MSG_MOUSE, id) {}
};


class MouseScrollMessage : public Message {
public:
	MouseScrollMessage(int id) : Message(MSG_MOUSE_SCROLL, id) {}
};

class MessagingBase {
	typedef void(*Handler)(MessagingBase*, const Message&);

	struct Binding {
		MessageType m_Type;
		MessagingBase* m_Observer;
		MessagingBase* m_Observed;
		Handler m_Handler;

		Binding(MessageType type, MessagingBase* observer,
			MessagingBase* observed, Handler handler) :
			m_Type(type), m_Observer(observer), m_Observed(observed),
			m_Handler(handler) {}
	};

	std::vector<Binding> m_Bindings;

public:
	~MessagingBase();

	template <typename Object, typename Param, void(Object::*Method)(const Param& param)>
	void Bind(MessageType type, Object* observer);
	template <typename Object, typename Param, void(Object::*Method)(const Param& param)>
	void Unbind(MessageType type, Object* observer);
	void Unbind(const MessagingBase* object);

protected:
	void SendMessage(const Message& msg);

private:
	template <typename Object, typename Param, void(Object::*Method)(Param param)>
	static void Binder(MessagingBase* observer, const Message& message) {
		(static_cast<Object*>(observer)->*Method)(static_cast<const Param&>(message));
	}
};

class Observed : public MessagingBase {
public:
	//void RaiseKey(int id) { SendMessage(KeyUpMessage(id)); }
	//void RaiseMouse(int id) { SendMessage(MouseMessage(id)); }
};

class Observer : public MessagingBase {
public:
	//void OnMessage(const Message& msg) { std::cout << "Got message id " << msg.m_Id << " of type " << msg.m_Type << std::endl; }
	//void OnKey(const KeyUpMessage& msg) { std::cout << "Got key message id " << msg.m_Id << std::endl; }
	//void OnMouse(const MouseMessage& msg) { std::cout << "Got mouse message id " << msg.m_Id << std::endl; }
	virtual void RegisterMsg() = 0;
};

template <typename Object, typename Param, void(Object::*Method)(const Param& param)>
void MessagingBase::Bind(MessageType type, Object* observer) 
{
	Binding binding(type, observer, this, &Binder<Object, const Param&, Method>);
	m_Bindings.push_back(binding);
	observer->m_Bindings.push_back(binding);
}

template <typename Object, typename Param, void(Object::*Method)(const Param& param)>
void MessagingBase::Unbind(MessageType type, Object* observer) 
{
	Handler handler = &Binder<Object, const Param&, Method>;
	auto i = m_Bindings.begin();
	while (i != m_Bindings.end())
		if (i->m_Type == type && i->m_Observer == observer && i->m_Handler == handler)
			i = m_Bindings.erase(i);
		else
			++i;
}

