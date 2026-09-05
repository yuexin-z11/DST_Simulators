# DST Simulators

ECE 6140 circuit simulation projects.

## Part 1: Boolean circuit simulator

[Project 1](p1/README.md) parses and simulates the four supplied circuit descriptions. It includes the general simulator, verification tests, all 20 required simulation results, and report material.

```bash
python3 p1/run_required.py
python3 -m unittest discover -s p1 -v
```

See [report material](p1/REPORT.md) and [simulation results](p1/results.md).

## Save future changes to GitHub

This workspace uses `main`, tracking `origin/main` at
`https://github.com/yuexin-z11/DST_Simulators.git`.

From `/mnt/d/ECE_6140`:

```bash
git status
git add p1 README.md RESUME_SESSION.md .gitignore
git commit -m "Describe your changes"
git push
```

Add future project folders explicitly to the `git add` command. Review `git status` before committing. Changes are uploaded only when you commit and push; the remote configuration persists between sessions. GitHub authentication is required on the machine making the push.

To work on another machine:

```bash
git clone https://github.com/yuexin-z11/DST_Simulators.git
cd DST_Simulators
```

Session continuation notes are in [RESUME_SESSION.md](RESUME_SESSION.md), outside the `p1` folder.
