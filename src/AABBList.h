/**
 * @class AABBList
 * @brief  AABB collision list array
 *
 * Updated Shay's Linklist format to a vector improving access speeds.
 *
 * @author Peter Crabbe
 * @version 02
 * @date 04/08/2019
 *
 */

#ifndef AABBLIST_H
#    define AABBLIST_H

#    include <vector>

#    include "AABBNode.h"
#    include "Glut.hpp"

class AABBList {
  public:
    /**
     * @brief Default constructor, not required
     */
    AABBList() = default;
    /**
     * @brief Default destructor, not required
     */
    ~AABBList() = default;

	/// Deleting the Copy constructor for safety reasons.
    AABBList(const AABBList &ll) = delete;

	/// Deleting the Copy assignment for safety reasons.
    AABBList &operator=(const AABBList &ll) = delete;

    /**
     * @brief  Attempts to add to the vector, then will push into the last spot
     *
     * @param  const int &ptrCount
     * @param  const GLfloat maxX
     * @param  const GLfloat minX
     * @param  const GLfloat maxY
     * @param  const GLfloat minY
     * @param  const GLfloat maxZ
     * @param  const GLfloat minZ
     * @return bool
     */
    bool AddToStart(GLfloat maxX, GLfloat minX, GLfloat maxY, GLfloat minY,
                    GLfloat maxZ, GLfloat minZ);

    /**
     * @brief  Sets the data at the given point in the array.
     *
     * @param  const int &ptrCount
     * @param  const GLfloat maxX
     * @param  const GLfloat minX
     * @param  const GLfloat maxY
     * @param  const GLfloat minY
     * @param  const GLfloat maxZ
     * @param  const GLfloat minZ
     * @return bool
     */
    void SetData(const int &ptrCount, const GLfloat maxX, const GLfloat minX,
                 const GLfloat maxY, const GLfloat minY, const GLfloat maxZ,
                 const GLfloat minZ);

    /**
     * @brief Gets the max X value at the given point in the array
     * @param int ptrCount
     * @return GLfloat
     */
    GLfloat GetMaxX(int ptrCount);

    /**
     * @brief Gets the max X value at the given point in the array
     * @param int ptrCount
     * @return GLfloat
     */
    GLfloat GetMinX(int ptrCount);

    /**
     * @brief Gets the max X value at the given point in the array
     * @param int ptrCount
     * @return GLfloat
     */
    GLfloat GetMaxY(int ptrCount);

    /**
     * @brief Gets the max X value at the given point in the array
     * @param int ptrCount
     * @return GLfloat
     */
    GLfloat GetMinY(int ptrCount);

    /**
     * @brief Gets the max X value at the given point in the array
     * @param int ptrCount
     * @return GLfloat
     */
    GLfloat GetMaxZ(int ptrCount);

    /**
     * @brief Gets the max X value at the given point in the array
     * @param int ptrCount
     * @return GLfloat
     */
    GLfloat GetMinZ(int ptrCount);

    /**
     * @brief Returns the size of the vector as an int.
     * @return GLfloat
     */
    int GetListSize();

    //--------------------------------------------------------------------------------------

  private:
    /// Vector storing the nodes.
    std::vector<AABBNode> nodes{};

    /**
     * @brief Depreciated Function, to be removed.
     */
    void Delete() {
        nodes.clear();
	}

    /**
     * @brief Depreciated Function, to be removed.
     */
    void Clear() {
        nodes.clear();
	}
};

#endif

//--------------------------------------------------------------------------------------
