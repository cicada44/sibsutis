#include <iostream>
#include <iomanip>
#include <cctype>
#include "cool-parse.h"
#include "utilities.h"

// padding 80 chars
static const char *padding = "                                                                                ";

void print_escaped_string(std::ostream &str, const char *s)
{
    while (*s) {
        switch (*s) {
        case '\\' : str << "\\\\"; break;
        case '\"' : str << "\\\""; break;
        case '\n' : str << "\\n"; break;
        case '\t' : str << "\\t"; break;
        case '\b' : str << "\\b"; break;
        case '\f' : str << "\\f"; break;

        default:
            if (std::isprint(*s))
                str << *s;
            else
                str << '\\' << std::oct << std::setfill('0') << std::setw(3)
                    << (int)((unsigned char)(*s))
                    << std::dec << std::setfill(' ');
            break;
        }
        s++;
    }
}

const char *cool_token_to_string(int tok)
{
    switch (tok) {
    case 0:            return("EOF");        break;
    case (CLASS):      return("CLASS");      break;
    case (ELSE):       return("ELSE");       break;
    case (FI):         return("FI");         break;
    case (IF):         return("IF");         break;
    case (IN):         return("IN");         break;
    case (INHERITS):   return("INHERITS");   break;
    case (LET):        return("LET");        break;
    case (LOOP):       return("LOOP");       break;
    case (POOL):       return("POOL");       break;
    case (THEN):       return("THEN");       break;
    case (WHILE):      return("WHILE");      break;
    case (ASSIGN):     return("ASSIGN");     break;
    case (CASE):       return("CASE");       break;
    case (ESAC):       return("ESAC");       break;
    case (OF):         return("OF");         break;
    case (DARROW):     return("DARROW");     break;
    case (NEW):        return("NEW");        break;
    case (STR_CONST):  return("STR_CONST");  break;
    case (INT_CONST):  return("INT_CONST");  break;
    case (BOOL_CONST): return("BOOL_CONST"); break;
    case (TYPEID):     return("TYPEID");     break;
    case (OBJECTID):   return("OBJECTID");   break;
    case (ERROR):      return("ERROR");      break;
    case (LE):         return("LE");         break;
    case (NOT):        return("NOT");        break;
    case (ISVOID):     return("ISVOID");     break;
    case '+': return("'+'"); break;
    case '/': return("'/'"); break;
    case '-': return("'-'"); break;
    case '*': return("'*'"); break;
    case '=': return("'='"); break;
    case '<': return("'<'"); break;
    case '.': return("'.'"); break;
    case '~': return("'~'"); break;
    case ',': return("','"); break;
    case ';': return("';'"); break;
    case ':': return("':'"); break;
    case '(': return("'('"); break;
    case ')': return("')'"); break;
    case '@': return("'@'"); break;
    case '{': return("'{'"); break;
    case '}': return("'}'"); break;
    default:  return("<Invalid Token>");
    }
}

void print_cool_token(int tok)
{
    std::cerr << cool_token_to_string(tok);

    switch (tok) {
    case (STR_CONST):
        std::cerr << " = ";
        std::cerr << " \"";
        print_escaped_string(std::cerr, cool_yylval.symbol->get_string());
        std::cerr << "\"";
        break;
    case (INT_CONST):
        std::cerr << " = " << cool_yylval.symbol;
        break;
    case (BOOL_CONST):
        std::cerr << (cool_yylval.boolean ? " = true" : " = false");
        break;
    case (TYPEID):
    case (OBJECTID):
        std::cerr << " = " << cool_yylval.symbol;
        break;
    case (ERROR):
        std::cerr << " = ";
        print_escaped_string(std::cerr, cool_yylval.error_msg);
        break;
    }
}

void dump_cool_token(std::ostream &out, int lineno, int token, YYSTYPE yylval)
{
    out << "#" << lineno << " " << cool_token_to_string(token);

    switch (token) {
    case (STR_CONST):
        out << " \"";
        print_escaped_string(out, cool_yylval.symbol->get_string());
        out << "\"";
        break;
    case (INT_CONST):
        out << " " << cool_yylval.symbol;
        break;
    case (BOOL_CONST):
        out << (cool_yylval.boolean ? " true" : " false");
        break;
    case (TYPEID):
    case (OBJECTID):
        out << " " << cool_yylval.symbol;
        break;
    case (ERROR):
        if (cool_yylval.error_msg[0] == 0) {
            out << " \"\\000\"";
        }
        else {
            out << " \"";
            print_escaped_string(out, cool_yylval.error_msg);
            out << "\"";
            break;
        }
    }
    out << std::endl;
}

const char *pad(int n)
{
    if (n > 80) return padding;
    if (n <= 0) return "";
    return padding+(80 - n);
}
