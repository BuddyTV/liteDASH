# DevSecOps Security Guidance

This repository is part of the organization-wide shift-left security initiative. The following automated security controls have been implemented to catch vulnerabilities and misconfigurations before they reach production.

---

## Branch Protection

As part of this initiative, the following branch protection rules are being enforced at the organization level for protected branches:

- **Pull requests required** — direct pushes to protected branches are not allowed
- **At least 1 reviewer required** — all PRs must have at least one approving review
- **Force pushes blocked** — branch history cannot be rewritten
- **Branch deletion blocked** — protected branches cannot be deleted
- If the Wiz IaC Scan and Dependency Review is present then,...
  - **Required status checks** — the Wiz IaC Scan and Dependency Review checks must pass before merging. PRs with critical findings will be blocked (requires review + remediation).

---

## Wiz IaC Scanning

### What it does

Scans Infrastructure-as-Code files (Terraform, YAML, JSON, Dockerfiles) for security misconfigurations such as publicly exposed resources, overly permissive IAM policies, unencrypted storage, and open security groups.

### How it works

- Triggers automatically on pull requests that modify IaC-related files
- Can also be triggered manually via workflow dispatch
- Calls a centralized reusable workflow maintained by the DevSecOps team

### What you will see

- A **Wiz IaC Scan** status check on your pull request
- A PR comment with a summary of findings grouped by severity (Critical, High, Medium, Low)
- Results uploaded to the repository's **Security** tab under Code Scanning

### How to address findings

- Review the findings in the PR comment or the Security tab
- CRITICAL (blocked) and High severity findings should be resolved before merging
- If a finding is a false positive, reach out to the DevSecOps team for guidance

---

## Dependency Review

### What it does

Checks all new or updated dependencies introduced in a pull request against known vulnerability databases (CVEs). This prevents merging code that pulls in packages with known security issues such as zero day exploits.

### How it works

- Triggers automatically on every pull request
- Compares the dependency changes in the PR against the GitHub Advisory Database

### What you will see

- A **dependency-review** status check on your pull request
- The check fails if any new dependency has a CRITICAL severity vulnerability

---

## Support

For questions, issues, or false positive reports, contact the DevSecOps team:

- **Email:** devsecops@vizio.com
- **Jira:** Create a ticket on the [DSEC Jira Board](https://vizio.atlassian.net) with:
  - The repository name
  - A description of the issue or finding in question
  - If False-Positive, provide reason or justification

If you do not have access to the DSEC Jira board, send an email with the details above.
