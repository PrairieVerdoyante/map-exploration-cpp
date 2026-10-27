#include "Backpack.h"


namespace HeArc::RPG {
	void Backpack::pack(std::shared_ptr<GameObject> _pObject) {
		m_Stack.push(_pObject);
	}
	std::shared_ptr<GameObject> Backpack::unpack() {
		
		std::shared_ptr<GameObject> pObject = m_Stack.top();
		m_Stack.pop();
		return pObject;
	}
	bool Backpack::isNotEmpty() {
		return !empty(m_Stack);
	}


} // namespace HeArc::RPG