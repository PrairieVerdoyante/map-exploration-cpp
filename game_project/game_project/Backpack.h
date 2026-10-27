#pragma once
#include <stack>
#include "GameObject.h"
#include "Diamond.h"
namespace HeArc::RPG {
    class Backpack
    {
    public:
        Backpack() = default;
        virtual ~Backpack() = default;

        /// <summary>
        /// Stores an object in the backpack.
        /// </summary>
        /// <param name="_pObject">The object to store in backpack</param>
        void pack(std::shared_ptr<GameObject> _pObject);

        /// <summary>
        /// Removes an object from the backpack.
        /// </summary>
        /// <returns>The modified backpack.</returns>
        std::shared_ptr<GameObject> unpack();

        /// <summary>
        /// Checks whether the backpack is empty or not
        /// </summary>
        bool isNotEmpty();

    private:
        std::stack<std::shared_ptr<GameObject>> m_Stack;
    };
}// namespace HeArc::RPG
