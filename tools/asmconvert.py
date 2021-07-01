import sys
import re

## Need to convert asxxxx syntax to rgbds syntax

module = sys.argv[1]

class Token:
    def __init__(self, kind, value, line_nr):
        self.kind = kind
        self.value = value
        self.line_nr = line_nr

    def isA(self, kind, value=None):
        return self.kind == kind and (value is None or value == self.value)

    def __repr__(self):
        return "[%s:%s:%d]" % (self.kind, self.value, self.line_nr)


class Tokenizer:
    TOKEN_REGEX = re.compile('|'.join('(?P<%s>%s)' % pair for pair in [
        ('HEX', r'0x[0-9A-Fa-f]+'),
        ('ASSIGN', r'='),
        ('ALABEL', r'\d+\$'),
        ('NUMBER', r'\d+(\.\d*)?'),
        ('COMMENT', r';[^\n]*'),
        ('LABEL', r':+'),
        ('EXPR', r'#'),
        ('STRING', '"[^"]*"'),
        ('DIRECTIVE', r'\.[A-Za-z_][A-Za-z0-9_\.]*'),
        ('ID', r'[A-Za-z_][A-Za-z0-9_\.]*'),
        ('OP', r'[+\-*/,\(\)<>]'),
        ('NEWLINE', r'\n'),
        ('SKIP', r'[ \t]+'),
        ('MISMATCH', r'.'),
    ]))

    def __init__(self, code):
        self.__tokens = []
        line_num = 1
        for mo in self.TOKEN_REGEX.finditer(code):
            kind = mo.lastgroup
            value = mo.group()
            if kind == 'MISMATCH':
                print("ERR:", code.split("\n")[line_num-1])
                raise RuntimeError("Syntax error on line: %d: %s\n%s", line_num, value)
            elif kind == 'SKIP':
                pass
            else:
                if kind == 'HEX':
                    value = "$" + value[2:]
                if kind == 'ALABEL':
                    value = "._ANNO_" + value[:-1]
                    kind = "ID"
                self.__tokens.append(Token(kind, value, line_num))
                if kind == 'NEWLINE':
                    line_num += 1
        self.__tokens.append(Token('NEWLINE', '\n', line_num))

    def peek(self):
        return self.__tokens[0]

    def pop(self):
        return self.__tokens.pop(0)

    def expect(self, kind, value=None):
        pop = self.pop()
        if not pop.isA(kind, value):
            if value is not None:
                raise SyntaxError("%s != %s:%s" % (pop, kind, value))
            raise SyntaxError("%s != %s" % (pop, kind))

    def __bool__(self):
        return bool(self.__tokens)

tok = Tokenizer(sys.stdin.read())

def processExpression():
    while True:
        t = tok.peek()
        if t.isA('EXPR'):
            tok.pop()
            t = tok.peek()
        if t.isA('OP', '<'):
            sys.stdout.write('LOW')
            tok.pop()
            t = tok.peek()
        if t.isA('OP', '>'):
            sys.stdout.write('HIGH')
            tok.pop()
            t = tok.peek()
        if t.isA('OP', '('):
            tok.pop()
            sys.stdout.write('(')
            processExpression()
            t = tok.pop()
            assert t.isA('OP', ')')
            sys.stdout.write(')')
        if t.isA('NEWLINE') or t.isA('OP', ')') or t.isA('OP', ','):
            break
        sys.stdout.write(t.value)
        tok.pop()

def processParameter():
    t = tok.pop()
    if t.isA('EXPR'):
        processExpression()
    elif t.isA('NEWLINE'):
        return
    elif t.isA('ID') or t.isA('NUMBER') or t.isA('HEX'):
        sys.stdout.write(t.value)
    elif t.isA('OP', '('):
        sys.stdout.write("[")
        processExpression()
        t = tok.pop()
        assert t.isA('OP', ')'), t
        sys.stdout.write("]")
    else:
        raise Exception(t)

while tok:
    start = tok.pop()
    if start.isA('NEWLINE'):
        pass
    elif start.isA('COMMENT'):
        print(start.value)
    elif start.isA('DIRECTIVE'):
        if start.value in {'.module', '.optsdcc', '.globl'}:
            while not tok.pop().isA('NEWLINE'):
                pass
        elif start.value == '.area':
            area_name = tok.pop().value
            if area_name == "_DATA":
                print('SECTION "%s_%s", WRAM0' % (module, area_name))
            elif area_name == "_DABS":
                print('SECTION "%s_%s", SRAM' % (module, area_name))
            elif area_name == "_HOME":
                print('SECTION FRAGMENT "%s_%s", ROM0' % (module, area_name))
            elif area_name == "_CODE":
                print('SECTION FRAGMENT "%s_%s", ROM0' % (module, area_name))
            elif area_name == "_CABS":
                print('SECTION FRAGMENT "%s_%s", ROM0' % (module, area_name))
            elif area_name == "_GSINIT":
                print('SECTION FRAGMENT "GSINIT", ROMX, BANK[1]')
            elif area_name == "_GSFINAL":
                print('SECTION FRAGMENT "GSFINAL", ROMX, BANK[1]')
            elif area_name == "_auto":
                print('SECTION FRAGMENT "code_%s", ROMX' % (module))
            else:
                raise Exception(area_name)
            while not tok.pop().isA('NEWLINE'):
                pass
        elif start.value == '.ds':
            sys.stdout.write("ds ")
            processExpression()
            sys.stdout.write("\n")
        elif start.value == '.ascii':
            sys.stdout.write("db ")
            sys.stdout.write(tok.pop().value)
            sys.stdout.write("\n")
        elif start.value == '.db':
            sys.stdout.write("db ")
            processParameter()
            while tok.peek().isA('OP', ','):
                sys.stdout.write(",")
                tok.pop()
                processParameter()
            sys.stdout.write("\n")
        else:
            raise Exception(start, tok.peek())
    elif start.isA('ID'):
        if tok.peek().isA('ASSIGN'):
            tok.pop()
            sys.stdout.write("%s = " % (start.value))
            processExpression()
            sys.stdout.write("\n")
        elif tok.peek().isA('LABEL'):
            print("%s%s" % (start.value, tok.pop().value))
        elif start.isA('ID', 'ldhl'):
            tok.expect('ID', 'sp')
            tok.expect('OP', ',')
            sys.stdout.write("ld hl, sp + ")
            processParameter()
            sys.stdout.write("\n")
        elif start.isA('ID', 'lda'):
            tok.expect('ID', 'hl')
            tok.expect('OP', ',')
            t = tok.pop()
            assert t.isA('NUMBER') or t.isA('HEX')
            tok.expect('OP', '(')
            tok.expect('ID', 'sp')
            tok.expect('OP', ')')
            sys.stdout.write("ld hl, sp + %s\n" % (t.value))
        else:
            sys.stdout.write("%s " % (start.value))
            if not tok.peek().isA('NEWLINE'):
                processParameter()
                if tok.peek().isA('OP', ','):
                    tok.pop()
                    sys.stdout.write(", ")
                    processParameter()
            sys.stdout.write("\n")
        tok.expect('NEWLINE')
    else:
        raise Exception(start)
