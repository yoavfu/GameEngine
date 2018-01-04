#pragma once
#include <iostream>
#include <vector>
#include <map>

enum MessageType {
	MSG_UNKNOWN = 0,
	MSG_KEYBOARD,
	MSG_MOUSE,
	MSG_MOUSE_SCROLL,
};

class Message 
{
public:
	MessageType m_Type;
	int m_Id;
	Message(MessageType type, int id) : m_Type(type), m_Id(id) {}
};

class MouseMessage : public Message 
{
public:
	MouseMessage(int id) : Message(MSG_MOUSE, id) {}
};


class MouseScrollMessage : public Message 
{
public:
	MouseScrollMessage(int id) : Message(MSG_MOUSE_SCROLL, id) {}
};

class Observer 
{
public:
	virtual void RegisterMsg() = 0;
};

class MessagingBase 
{
	typedef void(*Handler)(Observer*, const Message&);

	struct Binding 
	{
		Observer* observer_;
		Handler handler_;

		bool operator==(const Binding &other)
		{
			if (observer_ == other.observer_ && handler_ == other.handler_)
				return true;

			return false;
		}

		Binding(Observer* observer, Handler handler) :
			observer_(observer),
			handler_(handler) {}
	};

	std::map<MessageType, std::vector<Binding>> binding_;

public:
	~MessagingBase();

	template <typename Object, typename Param, void(Object::*Method)(const Param& param)>
	void Bind(MessageType type, Object* observer);
	template <typename Object, typename Param, void(Object::*Method)(const Param& param)>
	void Unbind(MessageType type, Object* observer);
	void Unbind(const Observer* object);

protected:
	void SendMessage(const Message& msg);

private:
	template <typename Object, typename Param, void(Object::*Method)(Param param)>
	static void Binder(Observer* observer, const Message& message) {
		(static_cast<Object*>(observer)->*Method)(static_cast<const Param&>(message));
	}
};

class Observed : public MessagingBase {
public:
};



template <typename Object, typename Param, void(Object::*Method)(const Param& param)>
void MessagingBase::Bind(MessageType type, Object* observer) 
{
	Binding binding(observer, &Binder<Object, const Param&, Method>);
	binding_[type].push_back(binding);
}

template <typename Object, typename Param, void(Object::*Method)(const Param& param)>
void MessagingBase::Unbind(MessageType type, Object* observer) 
{
	Binding binding(observer, &Binder<Object, const Param&, Method>);
	if (binding_.count(msg.m_Type))
	{
		auto it = std::find(vector.begin(), vector.end(), binding);
		if (it != vector.end())
			binding_[msg.m_Type].erase(it);
	}
}


