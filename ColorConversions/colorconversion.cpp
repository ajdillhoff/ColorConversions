#include <cstdlib>

extern "C" {
	unsigned char clip(int val) {
		if (val < 0) return 0;
		if (val > 255) return 255;
		return (unsigned char) val;
	}

	__declspec(dllexport) void __stdcall YUY2ToBGR(unsigned char *buffer_in, _Uint32t width, unsigned char *buffer_out, _Uint32t out_size) {
		for (int i = 0; i < width; i++) {
			int y0 = buffer_in[(i << 2) + 0] - 16;
			int u0 = buffer_in[(i << 2) + 1] - 128;
			int y1 = buffer_in[(i << 2) + 2] - 16;
			int v0 = buffer_in[(i << 2) + 3] - 128;
			buffer_out[(i << 3) + 0] = clip((298 * y0 + 516 * u0 + 128) >> 8); // blue
			buffer_out[(i << 3) + 1] = clip((298 * y0 - 100 * u0 - 208 * v0 + 128) >> 8); // green
			buffer_out[(i << 3) + 2] = clip((298 * y0 + 409 * v0 + 128) >> 8); // red
			buffer_out[(i << 3) + 3] = 0xFF;
			buffer_out[(i << 3) + 4] = clip((298 * y1 + 516 * u0 + 128) >> 8); // blue
			buffer_out[(i << 3) + 5] = clip((298 * y1 - 100 * u0 - 208 * v0 + 128) >> 8); // green
			buffer_out[(i << 3) + 6] = clip((298 * y1 + 409 * v0 + 128) >> 8); // red
			buffer_out[(i << 3) + 7] = 0xFF;
		}
	}
}
