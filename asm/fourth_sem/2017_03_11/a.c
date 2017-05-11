Переполнение sse регистров, че делать

uint32_t pop_count (uint32_t a)
{
	a = (a & 0x55555555) + ((a & 0xaaaaaaaa) >> 1);
	a = (a & 0x33333333) + ((a & 0xcccccccc) >> 2);
	a = (a & 0x0f0f0f0f) + ((a & 0xf0f0f0f0) >> 4);
	a = (a & 0x00ff00ff) + ((a & 0xff00ff00) >> 8);
	a = (a & 0xffff0000) + ((a & 0x0000ffff) >> 16);
} // что это?

см фото

