#include "Event.h"
#include <algorithm>

MessagingBase::~MessagingBase() 
{
	binding_.clear();
}

void MessagingBase::SendMessage(const Message& msg) 
{
	if (binding_.count(msg.m_Type))
	{
		for (Binding &bind : binding_[msg.m_Type])
			bind.handler_(bind.observer_, msg);
	}
}

void MessagingBase::Unbind(const Observer* object) 
{
	for (auto &bindVec : binding_)
	{
		struct IsSameObserver
		{
			explicit IsSameObserver(const Observer* object) : object_(object) { };
			inline bool operator()(const Binding other) const { return object_ == other.observer_; }
		private:
			const Observer *object_;
		};

		auto it = std::find_if(bindVec.second.begin(), bindVec.second.end(), IsSameObserver(object));
		if (it != bindVec.second.end())
			bindVec.second.erase(it);
	}
}