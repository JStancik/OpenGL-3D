#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <vector>

class Collider{
	public:
		Collider(std::vector<glm::vec3> verts);
		bool isColliding(Collider col1);
		glm::vec3 getCollision(Collider col1);
	private:
		std::vector<glm::vec3> verts;

		glm::vec3 dirToPoint(glm::vec3 dir);

		void handleCase();
		void pointCase(std::vector<glm::vec3> &points, glm::vec3 &dir);
		void lineCase (std::vector<glm::vec3> &points, glm::vec3 &dir);
		void triCase  (std::vector<glm::vec3> &points, glm::vec3 &dir);
		void tetraCase(std::vector<glm::vec3> &points, glm::vec3 &dir);
};