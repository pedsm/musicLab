workflow "New workflow" {
  on = "push"
  resolves = ["new-action"]
}

action "GitHub Action for npm" {
  uses = "actions/npm@3c8332795d5443adc712d30fa147db61fd520b5a"
  runs = "npm run dist"
}

action "new-action" {
  uses = "owner/repo/path@ref"
  needs = ["GitHub Action for npm"]
}
