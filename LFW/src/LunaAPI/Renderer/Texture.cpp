#include "LFWpch.h"
#include "Texture.h"

#include <glad/glad.h>

namespace Luna {

	Texture::Texture(const char* image)
	{
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //GL_LINEAR_MIPMAP_LINEAR //More smooth?
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //More pixelated?

		stbi_set_flip_vertically_on_load(true);
		int width, height, nrChannels;
		unsigned char* data = stbi_load(image, &width, &height, &nrChannels, 0);
		
		if (data)
		{
			GLenum format;
			switch (nrChannels)
			{
				case 1:
				{
					format = GL_LUMINANCE;
					break;
				}

				case 2:
				{
					format = GL_LUMINANCE_ALPHA;
					break;
				}

				case 3:
				{
					format = GL_RGB;
					break;
				}

				case 4:
				{
					format = GL_RGBA;
					break;
				}
			}


			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
			std::cout << "Loaded texture successfully\n";
		}
		else
		{
			std::cout << "Failed to load texture\n";
			//return;
		}

		stbi_image_free(data);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &id);
	}

	void Texture::Bind()
	{
		glBindTexture(GL_TEXTURE_2D, id);
	}

	void Texture::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
