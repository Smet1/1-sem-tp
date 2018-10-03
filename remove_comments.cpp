typedef enum {
  ST_USUAL,
  // we don't really need ST_SINGLELINE_COMMENT
  ST_MULTILINE_COMMENT,
  ST_STRING
} state_t;

state_t remove_cpp_comments(const char *line, state_t state) {
  for(const char *s = line; *s; s++)
  {
    switch(state) {
      case ST_USUAL:
        if (s[0] == '/' && s[1] == '/') {
          // simply ignore the rest of string
          putchar('\n');
          return ST_USUAL;
        }
        else if (s[0] == '/' && s[1] == '*') {
          state = ST_MULTILINE_COMMENT;
          s++;
        }
        else if (s[0] == '"')
          state = ST_STRING;
        break;

//hide_from
      case ST_MULTILINE_COMMENT:
        if (s[0] == '*' && s[1] == '/') {
          state = ST_USUAL;
          s += 1;
          continue;
        }
        break;

      case ST_STRING:
        if (s[0] == '"' && s > line && *(s - 1) != '\\')
          state = ST_USUAL;

        break;
//hide_to
    }

    if (state != ST_MULTILINE_COMMENT)
      putchar(*s);
  }

  return state;
}


int main() {
  string line;
  state_t state = ST_USUAL;

  // read STDIN line-by-line, since there may be really huge file
  while ( !getline(cin, line).eof() ) {
    line += '\n';
    state = remove_cpp_comments(line.c_str(), state);
  }

  return 0;
}