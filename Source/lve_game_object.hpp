#pragma once
#include "lve_model.hpp"
#include <memory>

namespace lve{

	struct Transform2dComponent {
		glm::vec2 translation{};	// position offset
		glm::vec2 scale{ 1.0f, 1.0f };
		float rotation;

		glm::mat2 mat2() { 
			const float s = glm::sin(rotation);
			const float c = glm::cos(rotation);
			glm::mat2 rotMat{ {c,s}, {-s,c} };
			glm::mat2 scaleMat{ {scale.x, 0.0f}, {0.0f, scale.y} };
			return rotMat * scaleMat; 
		}
	};

	class LveGameObject {
	public:
		using id_t = unsigned int;

		const id_t id;
		std::shared_ptr<LveModel> model{};
		glm::vec3 color{};
		Transform2dComponent transform2d;

		static LveGameObject CreateGameObject() {
			static id_t currentId = 0;
			return LveGameObject(currentId++);
		}
		LveGameObject(const LveGameObject&) = delete;
		LveGameObject& operator=(const LveGameObject&) = delete;
		LveGameObject(LveGameObject&&) = default;
		LveGameObject& operator=(LveGameObject&&) = default;

		id_t GetId() const { return id; }
	private:

		LveGameObject(id_t objId) : id{ objId } {};
	};
}  // namespace lve