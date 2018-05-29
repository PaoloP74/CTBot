#include "CTBotInlineKeyboard.h"

void CTBotInlineKeyboard::initialize(void)
{
	JsonObject& root = m_jsonBuffer.createObject();
	JsonArray&  rows = root.createNestedArray("inline_keyboard");
	JsonArray&  buttons = rows.createNestedArray();

	m_root = &root;
	m_rows = &rows;
	m_buttons = &buttons;
}

CTBotInlineKeyboard::CTBotInlineKeyboard()
{
	initialize();
}

CTBotInlineKeyboard::~CTBotInlineKeyboard()
{
}

void CTBotInlineKeyboard::flushData(void)
{
	m_jsonBuffer.clear();
	initialize();
}

void CTBotInlineKeyboard::addRow()
{
	JsonArray&  buttons = m_rows->createNestedArray();
	m_buttons = &buttons;
}

bool CTBotInlineKeyboard::addButton(String text, String command, CTBotInlineKeyboardType buttonType)
{
	JsonObject& button = m_buttons->createNestedObject();
	button["text"] = text;
	if (CTBotKeyboardButtonURL == buttonType)
		button["url"] = command;
	else if (CTBotKeyboardButtonQuery == buttonType)
	 	button["callback_data"] = command;
	else 
		return(false);
	return(true);
}

String CTBotInlineKeyboard::getJSON(void)
{
	String serialized;
	m_root->printTo(serialized);
	return(serialized);
}

