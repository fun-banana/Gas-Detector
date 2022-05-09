#include "bitmap.h"

#include <avr/pgmspace.h>

// #include <SdFat.h>

#include "ili9488.h"

namespace bmp {
	namespace details {
    constexpr PROGMEM uint16_t PIXELS{ 40 };
    constexpr PROGMEM uint32_t BI_RGB{  0 };
  
		struct BMPCOREHEADER
		{
			uint32_t bmp_size;
			uint16_t unused_1;
			uint16_t unused_2;
			uint32_t bmp_data_offset;
		};

		struct BMPINFOHEADER
		{
			uint32_t header_size;
			uint32_t bmp_width;
			int32_t  bmp_height;
			uint16_t color_panels;
			uint16_t bits_per_pixel;
			uint32_t compression_type;
			uint32_t raw_bmp_size;
			uint32_t horizontal_resolution;
			uint32_t vertical_resolution;
			uint32_t palette_colors;
			uint32_t important_colors;
		};
	}
}
// 	BMPStatus draw(char* file_name, uint16_t x, uint16_t y)
// 	{
//     if((x >= lcd.Get_Width()) || (y >= lcd.Get_Height()))
//       return BAD_XY;

//     // SdFile bmp_file{ file_name, O_READ };
//     if(!bmp_file.isOpen())
//       return FILE_NOT_FOUND;

//     details::BMPCOREHEADER core_header;
//     details::BMPINFOHEADER info_header;
//     char                   signature[2];

//     // bmp_file.read((char*)&signature, sizeof(signature));
//     if (signature[0] != 'B' && signature[1] != 'M') //windows signature
//       return BAD_ID;

//     bmp_file.read((char*)&core_header, sizeof(core_header));
//     bmp_file.read((char*)&info_header, sizeof(info_header));

//     if (info_header.compression_type != details::BI_RGB)
//       return COMPRESSED;

//     if (info_header.bits_per_pixel != 24)
//       return NOT_24_BIT;

//     if(info_header.bmp_height < 0) //only canon bmp files are supported
//       return BAD_BMP;

//     //Crop Area to be loaded
//     uint32_t cropped_width  = info_header.bmp_width;
//     int32_t  cropped_height = info_header.bmp_height;
//     if((x + cropped_width  - 1) >= lcd.Get_Width())  cropped_width  = lcd.Get_Width()  - x;
//     if((y + cropped_height - 1) >= lcd.Get_Height()) cropped_height = lcd.Get_Height() - y;

//     uint32_t padded_row_size{ (info_header.bmp_width * 3 + 3) & ~3 };
//     uint8_t  pixel_buf[3 * details::PIXELS];
//     uint8_t  pixel_index{ sizeof(pixel_buf)};
//     uint32_t row_offset;

//     for(uint16_t row{}; row < cropped_height; ++row) {
//       row_offset = core_header.bmp_data_offset + (info_header.bmp_height - 1 - row) * padded_row_size;
//       bmp_file.seekSet(row_offset);
//       pixel_index = sizeof(pixel_buf);
//       for(uint16_t col{}; col < cropped_width; ++col){
//         if (pixel_index >= sizeof(pixel_buf)) { 
//           bmp_file.read(pixel_buf, sizeof(pixel_buf));
//           pixel_index = 0; 
//         }
        
// 		lcd.Set_Draw_color(
// 			pixel_buf[pixel_index + 2], 
// 			pixel_buf[pixel_index + 1], 
// 			pixel_buf[pixel_index]
// 		);
// 		lcd.Draw_Pixel(col, row);

// 		pixel_index += 3;
//       }
//     }
//     bmp_file.close();
//     return GOOD_BMP;
// 	}
// }