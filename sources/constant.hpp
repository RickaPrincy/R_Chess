#pragma once

namespace constant
{
	inline constexpr const int window_size = 568;
	inline constexpr const int border_size = 20;
	inline constexpr const int case_size = 66;
	inline constexpr const int piece_size = 50;
	inline constexpr const int row_count = 8;
	inline constexpr const int column_count = 8;
	inline constexpr const int pieces_count = 32;
	inline constexpr const int padding_size = case_size - piece_size;
	inline constexpr const int max_coord_on_board = row_count * case_size + border_size;
	inline constexpr const int min_coord_on_board = border_size;
}  // namespace constant
