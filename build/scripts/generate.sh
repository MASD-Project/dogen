git_repo=/work/DomainDrivenConsulting/masd/dogen/master
git_branch=generated_code
commit_message="Generated code"

git clone ${git_repo} generated --max-depth=1
cd generated
git checkout ${git_branch}

#
# if last commit matches regex X revert the commit and commit the
# revert.
#
git merge master
git commit

export XX=
build/scripts/build.linux.sh Release 4 clang9 dogen.cli
build/scripts/build.linux.sh Release 4 clang9 gad
git add -A
git commit -m "${commit_message}"
git push origin ${git_branch}
