#!/usr/bin/env bash

# 사용법:
# 1) 드라이런(실제 변경 X): DRYRUN=1 ./remove_bonus_suffix.sh
# 2) 실제 변경:            ./remove_bonus_suffix.sh

set -euo pipefail

# -e : 중간에 어떤 명령이 실패(exit code != 0) 하면 스크립트 즉시 종료
# -u : 정의 안 된 변수 쓰면 종료 ($FOO가 없는데 쓰면 터짐)
#pipefail : A | B | C 파이프에서 중간이 실패해도 전체를 실패로 처리
#(기본 bash는 마지막 명령 성공하면 성공으로 보는 경우가 있음)

DRYRUN="${DRYRUN:-0}"
 # 테스트 실행에 사용
 # DRYRUN이 있으면사용하고 비어있으면 0을 사용하기


dir="$1" 

# 끝 슬래시 정리 ("/a/b/" -> "/a/b")
dir="${dir%/}"
  
rename_one() {
  local path="$1" 				# $1는 함수의 첫번째 인자 
  										
  										# 명령어를 사용하기 위해 소괄호를 사용 $()
  local base="$(basename -- "$path")"   # $ basename 이라는 명령어 실행, 이하 동일
  local newbase
  local newpath
  local prefix
  local ext

  if [[ "$base" == *_bonus.* ]]; then
	  prefix="${base%_bonus.*}"      # foo_bonus.h -> foo   %를 하면 뒤부터 일치하는 것을 잘라냄
	  ext="${base##*_bonus.}"        # foo_bonus.h -> h     ##를 하면 앞부터 일치하는 것을 잘라냄
	  newbase="${prefix}.${ext}"     # foo + . + h -> foo.h
  else
	  return 0
  fi

  newpath=${dir}/${newbase}

  if [[ -e "$newpath" ]]; then

	  echo "Skip (exists): $path -> $newpath" >&2
	  return 0
  fi

  if [[ "$DRYRUN" == "1" ]]; then
	  echo "DryRun: mv -- '$path' '$newpath'"
  else
	  mv -- "$path" "$newpath"
	  echo "Rename: $path -> $newpath"
  fi

}


for f in "$dir"/*_bonus.*; do
  rename_one "$f"
done
