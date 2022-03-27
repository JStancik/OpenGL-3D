#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <vector>

class Collider{
	public:
		Collider(std::vector<glm::vec4> verts);
		bool isColliding(Collider col1);
		glm::vec4 getCollision(Collider col1);
	private:
		std::vector<glm::vec4> verts;

		glm::vec4 dirToPoint(glm::vec4 dir);

		void handleCase();
		void pointCase(std::vector<glm::vec3> &points, glm::vec3 &dir);
		void lineCase (std::vector<glm::vec3> &points, glm::vec3 &dir);
		void triCase  (std::vector<glm::vec3> &points, glm::vec3 &dir);
		void tetraCase(std::vector<glm::vec3> &points, glm::vec3 &dir);
};