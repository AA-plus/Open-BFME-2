#!/usr/bin/env bash
# One-time per-clone setup. Run after every fresh clone (git does not enable
# tracked hooks or upstream tracking on its own).
set -euo pipefail

ROOT="$(git rev-parse --show-toplevel)"
cd "$ROOT"

git config core.hooksPath .githooks

# Agents work in a loop of pull --rebase / push against one shared master;
# tracking makes divergence visible in `git status`, pull.rebase makes a bare
# `git pull` do the right thing, and a non-interactive editor keeps rebases
# from hanging the session inside vim.
git branch --set-upstream-to=origin/master master 2>/dev/null \
    || echo "note: no origin/master yet; set upstream after first fetch"
git config pull.rebase true
git config core.editor true
# The merge=union ledgers: plain union brings back rows one side deleted or
# edited. Registered under git's own name so unregistered clones still merge.
# Worktrees share this config, so the command checks for its own files: a
# checkout older than the driver says so and merges as built-in union did
# (git merge-file --diff-algorithm, git 2.44 or newer; else a conflict).
# .githooks/pre-commit and tools/setup_local_fleet.py set the same command.
git config merge.union.name "union without resurrected rows (tools/merge_rows.py)"
git config merge.union.driver "if [ -f tools/merge_rows.py ] && [ -f .githooks/run-python3 ]; then sh .githooks/run-python3 tools/merge_rows.py %O %A %B %P; else echo 'merge.union.driver: tools/merge_rows.py or .githooks/run-python3 is not in this checkout; using git merge-file --union for' %P >&2; git merge-file --union --diff-algorithm=histogram '%A' '%O' '%B' || { echo 'merge.union.driver: git merge-file --union --diff-algorithm=histogram failed (it needs git 2.44 or newer); leaving a conflict in' %P >&2; exit 1; }; fi"
# A pull moves the reference/open-bfme-1 pin; without this its checkout stays
# behind and builds against stale headers (tools/build.py refuses to).
git config submodule.recurse true
git submodule update --init reference/open-bfme-1

echo "core.hooksPath=$(git config --get core.hooksPath)"
echo "upstream=$(git rev-parse --abbrev-ref --symbolic-full-name '@{u}' 2>/dev/null || echo unset)"
echo "pull.rebase=$(git config --get pull.rebase) core.editor=$(git config --get core.editor)"
echo "submodule.recurse=$(git config --get submodule.recurse)"
