#include <string>
#include <iostream>

#include "markdown.h"
#include "../md4c/md4c.h"

int Markdown::enter_block_callback(MD_BLOCKTYPE type, void* detail, void* userdata)
{
    static_cast<Markdown*>(userdata)->enter_block(type, detail);
}

int Markdown::leave_block_callback(MD_BLOCKTYPE type, void* detail, void* userdata)
{
    static_cast<Markdown*>(userdata)->leave_block(type, detail);
}

int Markdown::enter_span_callback(MD_SPANTYPE type, void* detail, void* userdata)
{
    static_cast<Markdown*>(userdata)->enter_span(type, detail);
}

int Markdown::leave_span_callback(MD_SPANTYPE type, void* detail, void* userdata)
{
    static_cast<Markdown*>(userdata)->leave_span(type, detail);
}

int Markdown::text_callback(MD_TEXTTYPE type, const MD_CHAR* text, MD_SIZE size, void* userdata)
{
    std::string s = text;
    static_cast<Markdown*>(userdata)->text(type, s.substr(0, size));
    // static_cast<Markdown*>(userdata)->text(type, std::string(text, text + size));
}

void Markdown::debug_log_callback(const char* msg, void* userdata)
{
    static_cast<Markdown*>(userdata)->debug_log(msg);
}

int Markdown::enter_block(MD_BLOCKTYPE type, void* /*detail*/)
{
    switch(type) {
        case MD_BLOCK_DOC:      /* noop */ break;
        case MD_BLOCK_QUOTE:    std::cout << "<..." << std::endl; break;
        case MD_BLOCK_UL:       std::cout << "<..." << std::endl;  break;
        case MD_BLOCK_OL:       std::cout << "<..." << std::endl;  break;
        case MD_BLOCK_LI:       std::cout << "<..." << std::endl;  break;
        case MD_BLOCK_HR:       std::cout << "<..." << std::endl;  break;
        case MD_BLOCK_H:        std::cout << "<title" << std::endl;  break;
        case MD_BLOCK_CODE:     std::cout << "<..." << std::endl;  break;
        case MD_BLOCK_HTML:     std::cout << "<..." << std::endl;  break;
        case MD_BLOCK_P:        std::cout << "<p" << std::endl;  break;
        case MD_BLOCK_TABLE:    std::cout << "<..." << std::endl;  break;
        case MD_BLOCK_THEAD:    std::cout << "<..." << std::endl;  break;
        case MD_BLOCK_TBODY:    std::cout << "<..." << std::endl;  break;
        case MD_BLOCK_TR:       std::cout << "<..." << std::endl;  break;
        case MD_BLOCK_TH:       std::cout << "<..." << std::endl;  break;
        case MD_BLOCK_TD:       std::cout << "<..." << std::endl;  break;
    }
    return 0;
}

int Markdown::leave_block(MD_BLOCKTYPE /*type*/, void* /*detail*/)
{
    return 0;
}

int Markdown::enter_span(MD_SPANTYPE type, void* /*detail*/)
{
    switch(type) {
        case MD_SPAN_EM:        std::cout << "<em..." << std::endl; break;
        case MD_SPAN_STRONG:    std::cout << "<strong..." << std::endl; break;
        case MD_SPAN_A:         std::cout << "<..." << std::endl; break;
        case MD_SPAN_IMG:       std::cout << "<..." << std::endl; break;
        case MD_SPAN_CODE:      std::cout << "<..." << std::endl; break;
    }

    return 0;
}

int Markdown::leave_span(MD_SPANTYPE /*type*/, void* /*detail*/)
{
    return 0;
}

int Markdown::text(MD_TEXTTYPE type, const std::string text)
{
    switch(type) {
        case MD_TEXT_NULLCHAR:  std::cout << "..." << std::endl; break; 
        case MD_TEXT_BR:        std::cout << "..." << std::endl; break; 
        case MD_TEXT_SOFTBR:    std::cout << "..." << std::endl; break; 
        case MD_TEXT_HTML:      std::cout << "html " << text << std::endl; break; 
        case MD_TEXT_ENTITY:    std::cout << "..." << std::endl; break; 
        default:                std::cout << text << std::endl; break;    
    }
    return 0;
}

void Markdown::debug_log(const char* msg)
{
}

void Markdown::parse()
{

    unsigned parser_flags = 0; // see md2html.c (options handling)
    unsigned renderer_flags = 0; // in the html example: debug(output to stderr) | verbatim_entities

    MD_RENDERER renderer = {
        Markdown::enter_block_callback,
        Markdown::leave_block_callback,
        Markdown::enter_span_callback,
        Markdown::leave_span_callback,
        Markdown::text_callback,
        Markdown::debug_log_callback,
        parser_flags
    };

    int status = md_parse(content.c_str(), content.size(), &renderer, (void*) this);
}
