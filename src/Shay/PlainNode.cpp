#include "PlainNode.hpp"

using Shay::PlainNode;

// Function depreciated, to be deleted when safe too.
void PlainNode::Clear() {}

/**
 * @brief  Modifies the slope
 *
 * @param tempType The slope type
 * @param tempXs X start location
 * @param tempXe X end location
 * @param tempYs Y start location
 * @param tempYe Y end location
 * @param tempZs Z start location
 * @param tempZe Z end location
 */
void PlainNode::SetData(Slope tempType, GLfloat tempXs, GLfloat tempXe,
                        GLfloat tempYs, GLfloat tempYe, GLfloat tempZs,
                        GLfloat tempZe) {
    m_type        = tempType;
    m_xPlainStart = tempXs;
    m_xPlainEnd   = tempXe;
    m_yPlainStart = tempYs;
    m_yPlainEnd   = tempYe;
    m_zPlainStart = tempZs;
    m_zPlainEnd   = tempZe;
}

/**
 * @brief  Returns the slope type
 * @return The slope type
 */
PlainNode::Slope PlainNode::GetType() {
    return m_type;
}

/**
 * @brief  Returns the X start coordinate of the slope
 * @return The X start coordinate
 */
GLfloat PlainNode::GetXstart() {
    return m_xPlainStart;
}

/**
 * @brief  Returns the X end coordinate of the slope
 * @return The X end coordinate
 */
GLfloat PlainNode::GetXend() {
    return m_xPlainEnd;
}

/**
 * @brief  Returns the Y start coordinate of the slope
 * @return The Y start coordinate
 */
GLfloat PlainNode::GetYstart() {
    return m_yPlainStart;
}

/**
 * @brief  Returns the Y end coordinate of the slope
 * @return The Y end coordinate
 */
GLfloat PlainNode::GetYend() {
    return m_yPlainEnd;
}

/**
 * @brief  Returns the Z start coordinate of the slope
 * @return The Z start coordinate
 */
GLfloat PlainNode::GetZstart() {
    return m_zPlainStart;
}

/**
 * @brief  Returns the Z end coordinate of the slope
 * @return The Z end coordinate
 */
GLfloat PlainNode::GetZend() {
    return m_zPlainEnd;
}
