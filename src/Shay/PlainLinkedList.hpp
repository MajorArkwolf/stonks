#pragma once

#include <vector>

#include "PlainNode.hpp"

namespace Shay {
    /**
     * @class PlainLinkedList
     * @brief Class used to store all data about the plains within Shay's World
     */
    class PlainLinkedList {
      public:
        /// Default constructor, set to default
        PlainLinkedList() = default;

        /// Copy constructor, set to default
        PlainLinkedList(const PlainLinkedList &array) = default;

        /// Overloaded assignment operator, set to default
        PlainLinkedList &operator=(const PlainLinkedList &array) = default;

        bool AddToStart(PlainNode::Slope tempType, GLfloat tempXs,
                        GLfloat tempXe, GLfloat tempYs, GLfloat tempYe,
                        GLfloat tempZs, GLfloat tempZe);

        void SetData(std::size_t ptrCount, PlainNode::Slope tempType,
                     GLfloat tempXs, GLfloat tempXe, GLfloat tempYs,
                     GLfloat tempYe, GLfloat tempZs, GLfloat tempZe);
        PlainNode::Slope GetType(std::size_t ptrCount);
        GLfloat GetXstart(std::size_t ptrCount);
        GLfloat GetXend(std::size_t ptrCount);
        GLfloat GetYstart(std::size_t ptrCount);
        GLfloat GetYend(std::size_t ptrCount);
        GLfloat GetZstart(std::size_t ptrCount);
        GLfloat GetZend(std::size_t ptrCount);
        std::size_t GetListSize();

      private:
        /// Vector containing PlainNodes
        std::vector<PlainNode> nodes{};
    };
}
