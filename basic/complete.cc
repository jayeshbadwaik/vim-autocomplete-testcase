#include <clang-c/Index.h>
#include <cstdlib>
#include <iostream>

/*
 * Compile with:
 * g++ complete.cc -o complete -lclang -L/usr/lib/llvm
 * Run with:
 * LIBCLANG_TIMING=1 ./complete file.cc line column [clang args...]
 */

int main(int argc, char** argv)
{
    if (argc < 4) {
        std::cout << argv[0] << " file.cc line colum [clang args...]"
                  << std::endl;
        return 1;
    }

    CXIndex idx = clang_createIndex(1, 0);
    if (!idx) {
        std::cerr << "createIndex failed" << std::endl;
        return 2;
    }

    CXTranslationUnit u = clang_parseTranslationUnit(idx, argv[1], argv + 4,
                        argc - 4, 0, 0,
                        CXTranslationUnit_PrecompiledPreamble
                        | CXTranslationUnit_PrecompiledPreamble);

    if (!u) {
        std::cerr << "parseTranslationUnit failed" << std::endl;
        return 2;
    }

    clang_reparseTranslationUnit(u, 0, 0, 0);

    int line = strtol(argv[2], 0, 10);
    int column = strtol(argv[3], 0, 10);
    CXCodeCompleteResults* res = clang_codeCompleteAt(u, argv[1],
                                                      line, column,
                                                      0, 0, 0);
    if (!res) {
        std::cerr << "Could not complete" << std::endl;
        return 2;
    }

    for (unsigned i = 0; i < clang_codeCompleteGetNumDiagnostics(res); i++) {
        const CXDiagnostic& diag = clang_codeCompleteGetDiagnostic(res, i);
        const CXString& s = clang_getDiagnosticSpelling(diag);
        std::cout << clang_getCString(s) << std::endl;
    }

    for (unsigned i = 0; i < res->NumResults; i++) {
        const CXCompletionString& str = res->Results[i].CompletionString;

        for (unsigned j = 0; j < clang_getNumCompletionChunks(str); j++) {
            if (clang_getCompletionChunkKind(str, j) != CXCompletionChunk_TypedText)
                continue;

            const CXString& out = clang_getCompletionChunkText(str, j);
            std::cout << clang_getCString(out);
        }

        std::cout << std::endl;
    }
    clang_disposeCodeCompleteResults(res);

    return 0;
}
