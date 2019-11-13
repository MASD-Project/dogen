export PATH=/home/marco/local/cmake-3.15.3-Linux-x86_64/bin:$PATH
export MASD_DIR=/work/DomainDrivenConsulting/masd
export CMAKE_TOOLCHAIN_FILE=${MASD_DIR}/vcpkg/masd/scripts/buildsystems/vcpkg.cmake

git_repo=file:///work/DomainDrivenConsulting/masd/dogen/master
git_branch=generated_code
commit_message="Generated code"
git_dir=generated

if [ ! -d "${git_dir}" ]; then
    git clone --depth=5 ${git_repo} ${git_dir}
    cd ${git_dir}
    git checkout -b ${git_branch}
else
    cd ${git_dir}
    git checkout master
    git pull origin master | grep "Already up to date."
    ret=$?
    if [ $ret -eq 0 ]; then
        echo "No changes in master, exiting."
        exit 0;
    fi
    git checkout ${git_branch}
fi

git --no-pager log --name-status HEAD^..HEAD | grep "${commit_message}" | grep -v Revert
ret=$?
if [ $ret -eq 0 ]; then
    git revert HEAD --no-edit
else
    echo "Not reverting commit".
fi

# git merge master -m "Auto-merge master."
# export DOGEN_FULL_GENERATION="1"
# build/scripts/build.linux.sh Release 6 clang9 dogen.cli
# build/scripts/build.linux.sh Release 6 clang9 gad
# git add -A
# git commit -m "${commit_message}"
# git push --set-upstream origin ${git_branch}
