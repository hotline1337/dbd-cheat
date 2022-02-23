#include <pch.h>
#include "../features.h"

void visuals::entities::run(const sdk::u_world* world, sdk::a_pawn* my_player, sdk::a_player_controller* player_controller) {
	auto levels = world->levels;
	for (auto i = 0; i < levels.size(); i++) {
		if (!levels.is_valid(i)) break;

		const auto level = levels[i];
		if (!level) continue;

		for (auto actors = 0; i < level->actors.size(); actors++) {
			if (!level || !level->actors.is_valid(actors)) break;

			const auto actor = level->actors[actors];
			if (!actor || !actor->root_component) continue;

			const auto distance = my_player->get_distance_to_string(actor);
			const auto location = actor->get_location();

			const auto my_camper = reinterpret_cast<sdk::a_camper_player*>(my_player);
			if (!my_camper) continue;

			// if the distance (in meters) between local and the entity is higher or equal to 30 don't render it
			if (my_player->get_distance_to(actor) * 0.01f >= 30) continue;

			if (settings.generator)
				generator::name(actor, distance, location, player_controller);

			if (settings.pallet)
				pallet::name(actor, distance, location, player_controller);

			if (settings.escape_door)
				escape_door::name(actor, distance, location, player_controller);

			if (settings.chest)
				chest::name(actor, distance, location, player_controller);

			if (settings.window)
				window::name(actor, distance, location, player_controller, my_camper);

			if (settings.totem)
				totem::name(actor, distance, location, player_controller);

			if (settings.hatch)
				hatch::name(actor, distance, location, player_controller);

			if (settings.bear_trap)
				bear_trap::name(actor, distance, location, player_controller);
		}
	}
}

void visuals::entities::generator::name(sdk::a_actor* actor, const std::wstring& distance, const sdk::vector location, sdk::a_player_controller* player_controller) {
	const auto generator = reinterpret_cast<sdk::a_generator*>(actor);
	if (!generator) return;

	if (generator->is_generator()) {
		std::wstring name;

		// if the generator is repaired, don't to render it
		if (generator->is_repaired) return;

		if (generator->is_blocked) {
			name.append(L"generator").append(L" [").append(distance).append(L"]").append(L" [").append(L"blocked").append(L"]");
		} else {
			name.append(L"generator").append(L" [").append(distance).append(L"]").append(L" [").append(generator->get_repair_percent()).append(L"%]");
		}

		sdk::vector_2d position{};
		if (player_controller->world_to_screen(location, position)) {
			render::text(position.x, position.y, name.c_str(), { 52, 134, 235, 255 });
		}
	}
}

void visuals::entities::pallet::name(sdk::a_actor* actor, const std::wstring& distance, const sdk::vector location, sdk::a_player_controller* player_controller) {
	const auto pallet = reinterpret_cast<sdk::a_pallet*>(actor);
	if (!pallet) return;

	if (pallet->is_pallet()) {
		std::wstring name;

		// if the pallet is destroyed, don't to render it
		if (pallet->state == sdk::e_pallet_state::destroyed) return;

		if (pallet->state == sdk::e_pallet_state::fallen) {
			name.append(L"pallet").append(L" [").append(distance).append(L"]").append(L" [").append(L"fallen").append(L"]");
		} else if (pallet->state == sdk::e_pallet_state::illusionary) {
			name.append(L"pallet").append(L" [").append(distance).append(L"]").append(L" [").append(L"illusionary").append(L"]");
		} else {
			name.append(L"pallet").append(L" [").append(distance).append(L"]");
		}

		sdk::vector_2d position{};
		if (player_controller->world_to_screen(location, position)) {
			render::text(position.x, position.y, name.c_str(), { 52, 134, 235, 255 });
		}
	}
}

void visuals::entities::chest::name(sdk::a_actor* actor, const std::wstring& distance, const sdk::vector location, sdk::a_player_controller* player_controller) {
	const auto chest = reinterpret_cast<sdk::a_chest*>(actor);
	if (!chest) return;

	if (chest->is_chest()) {
		std::wstring name;

		// if the chest is opened, don't to render it
		if (chest->has_been_searched) return;

		name.append(L"chest").append(L" [").append(distance).append(L"]");

		sdk::vector_2d position{};
		if (player_controller->world_to_screen(location, position)) {
			render::text(position.x, position.y, name.c_str(), { 52, 134, 235, 255 });
		}
	}
}

void visuals::entities::escape_door::name(sdk::a_actor* actor, const std::wstring& distance, const sdk::vector location, sdk::a_player_controller* player_controller) {
	const auto door = reinterpret_cast<sdk::a_escape_door*>(actor);
	if (!door) return;

	if (door->is_escape_door()) {
		std::wstring name;

		name.append(L"door").append(L" [").append(distance).append(L"]");

		sdk::vector_2d position{};
		if (player_controller->world_to_screen(location, position)) {
			render::text(position.x, position.y, name.c_str(), { 52, 134, 235, 255 });
		}
	}
}

void visuals::entities::window::name(sdk::a_actor* actor, const std::wstring& distance, const sdk::vector location, sdk::a_player_controller* player_controller, sdk::a_camper_player* my_player) {
	const auto window = reinterpret_cast<sdk::a_window*>(actor);
	if (!window) return;

	if (window->is_window()) {
		std::wstring name;

		if (window->is_window_blocked_for(my_player)) {
			name.append(L"window").append(L" [").append(distance).append(L"]").append(L" [").append(L"blocked").append(L"]");
		} else {
			name.append(L"window").append(L" [").append(distance).append(L"]");
		}

		sdk::vector_2d position{};
		if (player_controller->world_to_screen(location, position)) {
			render::text(position.x, position.y, name.c_str(), { 52, 134, 235, 255 });
		}
	}
}

void visuals::entities::totem::name(sdk::a_actor* actor, const std::wstring& distance, const sdk::vector location, sdk::a_player_controller* player_controller) {
	const auto totem = reinterpret_cast<sdk::a_totem*>(actor);
	if (!totem) return;

	if (totem->is_totem()) {
		std::wstring name;

		// if the totem is cleansed, don't render it
		if (totem->state == sdk::e_totem_state::cleansed) return;

		if (totem->state == sdk::e_totem_state::hex) {
			name.append(L"totem").append(L" [").append(distance).append(L"]").append(L" [").append(L"hex").append(L"]");
		} else if (totem->state == sdk::e_totem_state::boon) {
			name.append(L"totem").append(L" [").append(distance).append(L"]").append(L" [").append(L"boon").append(L"]");
		} else {
			name.append(L"totem").append(L" [").append(distance).append(L"]");
		}

		sdk::vector_2d position{};
		if (player_controller->world_to_screen(location, position)) {
			render::text(position.x, position.y, name.c_str(), { 52, 134, 235, 255 });
		}
	}
}

void visuals::entities::hatch::name(sdk::a_actor* actor, const std::wstring& distance, const sdk::vector location, sdk::a_player_controller* player_controller) {
	const auto hatch = reinterpret_cast<sdk::a_hatch*>(actor);
	if (!hatch) return;

	if (hatch->is_hatch()) {
		std::wstring name;

		if (hatch->state == sdk::e_hatch_state::hidden) {
			name.append(L"hatch").append(L" [").append(distance).append(L"]").append(L" [").append(L"hidden").append(L"]");
		} else if (hatch->state == sdk::e_hatch_state::default_close || hatch->state == sdk::e_hatch_state::forced_close) {
			name.append(L"hatch").append(L" [").append(distance).append(L"]").append(L" [").append(L"closed").append(L"]");
		} else if (hatch->state == sdk::e_hatch_state::opened) {
			name.append(L"hatch").append(L" [").append(distance).append(L"]").append(L" [").append(L"opened").append(L"]");
		}

		sdk::vector_2d position{};
		if (player_controller->world_to_screen(location, position)) {
			render::text(position.x, position.y, name.c_str(), { 52, 134, 235, 255 });
		}
	}
}

void visuals::entities::bear_trap::name(sdk::a_actor* actor, const std::wstring& distance, const sdk::vector location, sdk::a_player_controller* player_controller) {
	const auto bear_trap = reinterpret_cast<sdk::a_bear_trap*>(actor);
	if (!bear_trap) return;

	if (bear_trap->is_bear_trap()) {
		std::wstring name;

		name.append(L"bear_trap").append(L" [").append(distance).append(L"]");

		sdk::vector_2d position{};
		if (player_controller->world_to_screen(location, position)) {
			render::text(position.x, position.y, name.c_str(), { 52, 134, 235, 255 });
		}
	}
}