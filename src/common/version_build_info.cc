/****************************************************************************
 *
 *      This is part of the libYafaRay-Gui package
 *
 *      This library is free software; you can redistribute it and/or
 *      modify it under the terms of the GNU Lesser General Public
 *      License as published by the Free Software Foundation; either
 *      version 2.1 of the License, or (at your option) any later version.
 *
 *      This library is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *      Lesser General Public License for more details.
 *
 *      You should have received a copy of the GNU Lesser General Public
 *      License along with this library; if not, write to the Free Software
 *      Foundation,Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 */

#include "common/version_build_info.h"
#include "yafaray_gui_version_build_info.h"

namespace yafaray_gui
{

std::string build_info::getVersionString() { return YAFARAY_GUI_VERSION_STRING + getGitLine(false); }
std::string build_info::getVersionDescription() { return YAFARAY_GUI_VERSION_DESCRIPTION; }
int build_info::getVersionMajor() { return YAFARAY_GUI_VERSION_MAJOR; }
int build_info::getVersionMinor() { return YAFARAY_GUI_VERSION_MINOR; }
int build_info::getVersionPatch() { return YAFARAY_GUI_VERSION_PATCH; }
std::string build_info::getVersionPreRelease() { return YAFARAY_GUI_VERSION_PRE_RELEASE; }
std::string build_info::getVersionPreReleaseDescription() { return YAFARAY_GUI_VERSION_PRE_RELEASE_DESCRIPTION; }
std::string build_info::getGitDescribe() { return YAFARAY_GUI_VERSION_GIT; }
std::string build_info::getGitTag() { return YAFARAY_GUI_VERSION_GIT_TAG; }
std::string build_info::getGitBranch() { return YAFARAY_GUI_VERSION_GIT_BRANCH; }
std::string build_info::getGitDirty() { return YAFARAY_GUI_VERSION_GIT_DIRTY; }
std::string build_info::getGitCommit() { return YAFARAY_GUI_VERSION_GIT_COMMIT; }
std::string build_info::getGitCommitDateTime() { return YAFARAY_GUI_VERSION_GIT_COMMIT_DATETIME; }
std::string build_info::getCommitsSinceTag() { return YAFARAY_GUI_VERSION_GIT_COMMITS_SINCE_TAG; }
std::string build_info::getBuildArchitectureBits() { return YAFARAY_GUI_BUILD_ARCHITECTURE_BITS; }
std::string build_info::getBuildCompiler() { return YAFARAY_GUI_BUILD_COMPILER; }
std::string build_info::getBuildCompilerVersion() { return YAFARAY_GUI_BUILD_COMPILER_VERSION; }
std::string build_info::getBuildOs() { return YAFARAY_GUI_BUILD_OS; }
std::string build_info::getBuildType() { return YAFARAY_GUI_BUILD_TYPE; }
std::string build_info::getBuildOptions() { return YAFARAY_GUI_BUILD_OPTIONS; }
std::string build_info::getBuildFlags() { return YAFARAY_GUI_BUILD_FLAGS; }
std::string build_info::getBuildTypeSuffix()
{
	const std::string build_type = getBuildType();
	if(build_type.empty() || build_type == "RELEASE") return "";
	else return "/" + build_type;
}

std::string build_info::getGitLine(bool long_line)
{
	// If no Git data or it's just master branch without any changes since last tag, then return an empty string
	std::string branch = getGitBranch();
	if(branch == "master") branch.clear();
	std::string commits_since_tag = getCommitsSinceTag();
	if(commits_since_tag == "0") commits_since_tag.clear();
	const std::string dirty = getGitDirty();

	if(branch.empty() && dirty.empty() && commits_since_tag.empty()) return "";
	std::string result = "+git";
	if(long_line)
	{
		if(!branch.empty()) result += "." + branch;
		result += "." + getGitTag();
		if(!commits_since_tag.empty()) result += ".+" + commits_since_tag;
	}
	result += ".g" + getGitCommit().substr(0, 8);
	if(!dirty.empty()) result += ".dirty";
	return result;
}

std::vector<std::string> build_info::getAllBuildDetails()
{
	std::vector<std::string> result;
	result.emplace_back("Version = '" + getVersionString() + "'");
	result.emplace_back("VersionDescription = '" + getVersionDescription() + "'");
	result.emplace_back("VersionState = '" + getVersionPreRelease() + "'");
	result.emplace_back("VersionStateDescription = '" + getVersionPreReleaseDescription() + "'");
	result.emplace_back("GitDescribe = '" + getGitDescribe() + "'");
	result.emplace_back("GitShortLine = '" + getGitLine(false) + "'");
	result.emplace_back("GitLongLine = '" + getGitLine(true) + "'");
	result.emplace_back("GitTag = '" + getGitTag() + "'");
	result.emplace_back("GitBranch = '" + getGitBranch() + "'");
	result.emplace_back("GitDirty = '" + getGitDirty() + "'");
	result.emplace_back("GitCommit = '" + getGitCommit() + "'");
	result.emplace_back("GitCommitDateTime = '" + getGitCommitDateTime() + "'");
	result.emplace_back("CommitsSinceTag = '" + getCommitsSinceTag() + "'");
	result.emplace_back("BuildArchitectureBits = '" + getBuildArchitectureBits() + "'");
	result.emplace_back("BuildCompiler = '" + getBuildCompiler() + "'");
	result.emplace_back("BuildCompilerVersion = '" + getBuildCompilerVersion() + "'");
	result.emplace_back("BuildOs = '" + getBuildOs() + "'");
	result.emplace_back("BuildType = '" + getBuildType() + "'");
	result.emplace_back("BuildOptions = '" + getBuildOptions() + "'");
	result.emplace_back("BuildCompilerFlags = '" + getBuildFlags() + "'");
	return result;
}

} // namespace yafaray_gui
