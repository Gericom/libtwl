#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/// @brief Atomically reads the byte at ptr and writes newValue.
/// @param newValue The value to write.
/// @param ptr The pointer to the byte to swap.
/// @return The old value read from ptr.
extern u8 mem_swapByte(u8 newValue, vu8* ptr);

/// @brief Atomically reads the word at ptr and writes newValue.
/// @param newValue The value to write.
/// @param ptr The pointer to the word to swap.
/// @return The old value read from ptr.
extern u32 mem_swapWord(u32 newValue, vu32* ptr);

#ifdef __cplusplus
}
#endif
