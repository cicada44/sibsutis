#!/bin/bash

start_date="2023-03-26"
end_date="2023-06-29"

current_date="$start_date"
while [[ "$current_date" != "$end_date" ]]; do
  num_commits=1

  for (( i=1; i<=$num_commits; i++ )); do
    commit_date="$(date -d "$current_date" +%Y-%m-%d)"
    commit_message="Commit $i on $commit_date"
    echo "Creating commit: $commit_message"

    # Change system date
    sudo date --set="$commit_date"

    # Git add command to stage changes
    git add --all

    # Commit changes
    git commit --allow-empty -m "$commit_message"
  done

  current_date=$(date -I -d "$current_date + 1 day")
done
