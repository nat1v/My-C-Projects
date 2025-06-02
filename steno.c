#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#pragma pack(push, 1)
typedef struct {
    uint16_t type;
    uint32_t size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset;
} BMPHeader;

typedef struct {
    uint32_t size;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bits_per_pixel;
    uint32_t compression;
    uint32_t image_size;
    int32_t x_pixels_per_meter;
    int32_t y_pixels_per_meter;
    uint32_t colors_used;
    uint32_t colors_important;
} BMPInfoHeader;
#pragma pack(pop)

typedef struct {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
} Pixel;

int read_bmp_file(const char* filename, BMPHeader* header, BMPInfoHeader* info_header, Pixel** pixels) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        printf("Error: Cannot open file %s\n", filename);
        return 0;
    }

    // Read BMP header
    fread(header, sizeof(BMPHeader), 1, file);
    
    // Check if it's a valid BMP file
    if (header->type != 0x4D42) {
        printf("Error: Not a valid BMP file\n");
        fclose(file);
        return 0;
    }

    // Read info header
    fread(info_header, sizeof(BMPInfoHeader), 1, file);
    
    // Check if it's 24-bit BMP
    if (info_header->bits_per_pixel != 24) {
        printf("Error: Only 24-bit BMP files are supported\n");
        fclose(file);
        return 0;
    }

    // Calculate padding
    int padding = (4 - (info_header->width * 3) % 4) % 4;
    
    // Allocate memory for pixels
    *pixels = malloc(info_header->width * info_header->height * sizeof(Pixel));
    if (!*pixels) {
        printf("Error: Memory allocation failed\n");
        fclose(file);
        return 0;
    }

    // Move to pixel data
    fseek(file, header->offset, SEEK_SET);
    
    // Read pixels (BMP stores bottom-to-top)
    for (int y = info_header->height - 1; y >= 0; y--) {
        for (int x = 0; x < info_header->width; x++) {
            int index = y * info_header->width + x;
            fread(&(*pixels)[index], sizeof(Pixel), 1, file);
        }
        // Skip padding bytes
        fseek(file, padding, SEEK_CUR);
    }

    fclose(file);
    return 1;
}

int write_bmp_file(const char* filename, BMPHeader* header, BMPInfoHeader* info_header, Pixel* pixels) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        printf("Error: Cannot create file %s\n", filename);
        return 0;
    }

    // Write headers
    fwrite(header, sizeof(BMPHeader), 1, file);
    fwrite(info_header, sizeof(BMPInfoHeader), 1, file);

    // Calculate padding
    int padding = (4 - (info_header->width * 3) % 4) % 4;
    uint8_t pad_bytes[3] = {0, 0, 0};

    // Write pixels (BMP stores bottom-to-top)
    for (int y = info_header->height - 1; y >= 0; y--) {
        for (int x = 0; x < info_header->width; x++) {
            int index = y * info_header->width + x;
            fwrite(&pixels[index], sizeof(Pixel), 1, file);
        }
        // Write padding bytes
        if (padding > 0) {
            fwrite(pad_bytes, padding, 1, file);
        }
    }

    fclose(file);
    return 1;
}

void hide_bit_in_byte(uint8_t* byte, int bit) {
    *byte = (*byte & 0xFE) | (bit & 1);
}

int extract_bit_from_byte(uint8_t byte) {
    return byte & 1;
}

void hide_message(Pixel* pixels, int pixel_count, const char* message) {
    int message_len = strlen(message);
    int bit_index = 0;
    int pixel_index = 0;
    
    // Hide each character
    for (int i = 0; i < message_len && pixel_index < pixel_count; i++) {
        char c = message[i];
        
        // Hide 8 bits of the character
        for (int bit = 0; bit < 8 && pixel_index < pixel_count; bit++) {
            int bit_value = (c >> bit) & 1;
            
            // Hide bit in RGB components (3 bits per pixel)
            if (bit_index % 3 == 0) {
                hide_bit_in_byte(&pixels[pixel_index].red, bit_value);
            } else if (bit_index % 3 == 1) {
                hide_bit_in_byte(&pixels[pixel_index].green, bit_value);
            } else {
                hide_bit_in_byte(&pixels[pixel_index].blue, bit_value);
                pixel_index++;
            }
            bit_index++;
        }
    }
    
    // Add null terminator (8 zero bits)
    for (int bit = 0; bit < 8 && pixel_index < pixel_count; bit++) {
        if (bit_index % 3 == 0) {
            hide_bit_in_byte(&pixels[pixel_index].red, 0);
        } else if (bit_index % 3 == 1) {
            hide_bit_in_byte(&pixels[pixel_index].green, 0);
        } else {
            hide_bit_in_byte(&pixels[pixel_index].blue, 0);
            pixel_index++;
        }
        bit_index++;
    }
}

void extract_message(Pixel* pixels, int pixel_count, char* message, int max_len) {
    int bit_index = 0;
    int pixel_index = 0;
    int char_index = 0;
    char current_char = 0;
    int bits_read = 0;
    
    message[0] = '\0';
    
    while (pixel_index < pixel_count && char_index < max_len - 1) {
        int bit_value = 0;
        
        // Extract bit from RGB components
        if (bit_index % 3 == 0) {
            bit_value = extract_bit_from_byte(pixels[pixel_index].red);
        } else if (bit_index % 3 == 1) {
            bit_value = extract_bit_from_byte(pixels[pixel_index].green);
        } else {
            bit_value = extract_bit_from_byte(pixels[pixel_index].blue);
            pixel_index++;
        }
        
        // Build character bit by bit
        current_char |= (bit_value << bits_read);
        bits_read++;
        bit_index++;
        
        // When we have 8 bits, we have a complete character
        if (bits_read == 8) {
            if (current_char == 0) {
                // Found null terminator, stop reading
                break;
            }
            message[char_index] = current_char;
            char_index++;
            current_char = 0;
            bits_read = 0;
        }
    }
    
    message[char_index] = '\0';
}

int main() {
    int choice;
    char filepath[256];
    char message[4];
    char extracted_message[256];
    
    BMPHeader header;
    BMPInfoHeader info_header;
    Pixel* pixels = NULL;
    
    printf("BMP Steganography Program\n");
    printf("========================\n");
    printf("1. Write message\n");
    printf("2. Decode message\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    
    switch (choice) {
        case 1:
            printf("\n1.1 Type the character (Max 3): ");
            scanf("%s", message);
            
            // Limit message to 3 characters
            if (strlen(message) > 3) {
                message[3] = '\0';
                printf("Message truncated to 3 characters: %s\n", message);
            }
            
            printf("Enter BMP file path: ");
            scanf("%s", filepath);
            
            if (!read_bmp_file(filepath, &header, &info_header, &pixels)) {
                return 1;
            }
            
            int pixel_count = info_header.width * info_header.height;
            int required_pixels = (strlen(message) + 1) * 8 / 3 + 1; // +1 for null terminator
            
            if (required_pixels > pixel_count) {
                printf("Error: Image too small to hide the message\n");
                free(pixels);
                return 1;
            }
            
            hide_message(pixels, pixel_count, message);
            
            // Create output filename
            char output_filename[256];
            strcpy(output_filename, "encoded_");
            strcat(output_filename, strrchr(filepath, '/') ? strrchr(filepath, '/') + 1 : filepath);
            
            if (write_bmp_file(output_filename, &header, &info_header, pixels)) {
                printf("Message hidden successfully in: %s\n", output_filename);
            }
            
            free(pixels);
            break;
            
        case 2:
            printf("Enter BMP file path: ");
            scanf("%s", filepath);
            
            if (!read_bmp_file(filepath, &header, &info_header, &pixels)) {
                return 1;
            }
            
            pixel_count = info_header.width * info_header.height;
            extract_message(pixels, pixel_count, extracted_message, sizeof(extracted_message));
            
            printf("Extracted message: \"%s\"\n", extracted_message);
            
            free(pixels);
            break;
            
        default:
            printf("Invalid choice!\n");
            return 1;
    }
    
    return 0;
}
