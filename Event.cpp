#include "Event.h"

MessagingBase::~MessagingBase() {
	while (!m_Bindings.empty()) {
		Binding binding = m_Bindings.back();
		m_Bindings.pop_back();
		binding.m_Observed->Unbind(this);
		binding.m_Observer->Unbind(this);
	};
}

void MessagingBase::SendMessage(const Message& msg) {
	for (size_t i = 0; i < m_Bindings.size(); ++i)
		if (m_Bindings[i].m_Type == MSG_UNKNOWN || m_Bindings[i].m_Type == msg.m_Type)
			m_Bindings[i].m_Handler(m_Bindings[i].m_Observer, msg);
}

void MessagingBase::Unbind(const MessagingBase* object) {
	auto i = m_Bindings.begin();
	while (i != m_Bindings.end())
		if (i->m_Observed == object || i->m_Observer == object)
			i = m_Bindings.erase(i);
		else
			++i;
}