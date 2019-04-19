import ParserV2Listener
import ParserV2Lexer
import ParserV2Parser
from antlr4 import *   

def main():
    lexer = ParserV2Lexer.ParserV2Lexer(StdinStream())
    stream = CommonTokenStream(lexer)
    parser = ParserV2Parser.ParserV2Parser(stream)
    tree = parser.startRule()

if __name__ == '__main__':
    main()
