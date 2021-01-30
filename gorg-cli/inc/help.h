#pragma once

#include <string>
#include <filesystem>

const std::string help_main =
	"usage gorg: [--version|-v] [--help|-h] <command> [<args>]\n"
	"\n"
	"These are common Gorg commands in various situations:\n"
	"\n"
	"primary commands (see also: gorg help tutorial)\n"
	"   asset       Create, edit or validate a gorg asset\n"
	"   generate    Generate searchable html index\n"
	"\n"
	"See 'gorg <command> --help' to read about a specific\n"
	"subcommand";

//
//	TODO - Unit tests to check existence of help docs
//
static const std::filesystem::path help_asset("../docs/commands/asset.html");
static const std::filesystem::path help_generate("../docs/commands/generate.html");