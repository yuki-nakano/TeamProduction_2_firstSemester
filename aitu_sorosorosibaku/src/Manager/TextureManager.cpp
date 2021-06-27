#include "TextureManager.h"

void TextureManager::LoadTextures()
{
	for (int i = 0; i < (int)TextureDate::kTextureMax; i++)
	{
		textureDate[i] = LoadGraph(pass[i]);
	}

}

void TextureManager::DeleteTextures()
{
	for (int i = 0; i < (int)TextureDate::kTextureMax; i++)
	{
		DeleteGraph(textureDate[i]);
	}
}

int TextureManager::GetTextureDate(TextureDate num)
{
	return textureDate[(int)num];
}
