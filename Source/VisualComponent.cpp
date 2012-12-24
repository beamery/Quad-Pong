#include "Actor.h"

VisualComponent::~VisualComponent()
{

}

void VisualComponent::init(XMLElement *xmlData)
{
	XMLElement *visibleElt = xmlData->FirstChildElement("Visible");
	// if no visibility if specified, default to true
	if (visibleElt == nullptr)
		visible = true;
	else
	{
		visible = visibleElt->BoolAttribute("value");
	}

	XMLElement *textureElt = xmlData->FirstChildElement("Texture");
	// if no texture is specified, set it to null
	if (textureElt == nullptr)
		texture = nullptr;
	else
	{
		string texID = textureElt->Attribute("id");
		texture = TextureManager::get()->getTexture(texID);
	}

	XMLElement *dimElt = xmlData->FirstChildElement("Dimensions");
	// if both are null, we have no dimension data
	if (dimElt == nullptr && textureElt == nullptr)
		throw BAD_DIMENSION_ERR;
	// if no dimensions are specified, take them from the texture
	else if (dimElt == nullptr)
	{
		width = texture->width;
		height = texture->height;
	}
	else
	{
		width = dimElt->DoubleAttribute("w");
		height = dimElt->DoubleAttribute("h");
	}


	XMLElement *colorElt = xmlData->FirstChildElement("Color");
	// if no color is specified, default to white
	if (colorElt == nullptr)
		colorData = bm::Color(255, 255, 255, 255);
	else
	{
		int r = colorElt->IntAttribute("r");
		int g = colorElt->IntAttribute("g");
		int b = colorElt->IntAttribute("b");
		int a = colorElt->IntAttribute("a");
		colorData = bm::Color(r, g, b, a);
	}
}

void VisualComponent::postInit()
{
	Vec2D<double> vTL(-width / 2.0f, -height / 2.0f);
	Vec2D<double> vBL(-width / 2.0f, height / 2.0f);
	Vec2D<double> vBR(width / 2.0f, height / 2.0f);
	Vec2D<double> vTR(width / 2.0f, -height / 2.0f);
	Vec2D<double> texTL(0, 0);
	Vec2D<double> texBL(0, 1);
	Vec2D<double> texTR(1, 0);
	Vec2D<double> texBR(1, 1);

	// TL, BL, TR, BR
	vertexData.push_back(vTL);
	vertexData.push_back(vBL);
	vertexData.push_back(vTR);
	vertexData.push_back(vBR);
	textureData.push_back(texTL);
	textureData.push_back(texBL);
	textureData.push_back(texTR);
	textureData.push_back(texBR);
}

void VisualComponent::update(double totalTime, double elapsedTime)
{

}

void VisualComponent::print()
{
	cout << "visible: \t" << boolalpha << visible << endl;
	if (texture != nullptr)
	{
		cout << "texture: " << endl;
		cout << "\t" << "id: " << texture->id << endl;
		cout << "\t" << "width: " << texture->width << endl;
		cout << "\t" << "height: " << texture->height << endl;
	}
	cout << "width: \t\t" << width << endl;
	cout << "height: \t" << height << endl;
	cout << "color: \t\t(";
	cout << colorData.r << ", ";
	cout << colorData.g << ", ";
	cout << colorData.b << ", ";
	cout << colorData.a << ")" << endl;

	cout << "vertices:" << endl;
	for (auto i = vertexData.begin(); i != vertexData.end(); i++)
	{
		cout << " (" << i->x << ", " << i->y << ")" << endl;
	}

	cout << "texture UVs:" << endl;
	for (auto i = textureData.begin(); i != textureData.end(); i++)
	{
		cout << " (" << i->x << ", " << i->y << ")" << endl;
	}


}
