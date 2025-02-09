#pragma once

namespace sdk {
	enum class e_totem_state : std::uint8_t {
		cleansed = 0,
		dull = 1,
		hex = 2,
		boon = 3,
		max = 4
	};

	struct a_totem : sdk::a_actor {
		char pad_0001[0x220]; // 0x148(0x220)
		sdk::e_totem_state state; // 0x368(0x01)

		bool is_totem() const;
	};
}