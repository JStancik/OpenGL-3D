#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <vector>
#include <object.hpp>

class Collider{
	public:
		Collider(std::vector<glm::vec3> verts);
		void updateCollider();
		bool isColliding(Collider col1);
		glm::vec3 getCollision(Collider col1);
		std::vector<glm::vec3> verts;
		glm::vec3 dirToPoint(glm::vec3 dir);
	private:
		glm::vec3 Collider::getSupPoint(Collider col1,glm::vec3 dir);
		bool handleCase(std::vector<glm::vec3> &points, glm::vec3 &dir);
		void pointCase (std::vector<glm::vec3> &points, glm::vec3 &dir);
		bool lineCase  (std::vector<glm::vec3> &points, glm::vec3 &dir);
		bool triCase   (std::vector<glm::vec3> &points, glm::vec3 &dir);
		bool tetraCase (std::vector<glm::vec3> &points, glm::vec3 &dir);
};