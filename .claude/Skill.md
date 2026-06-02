---
name: cpptest-fix-all-violations
description: "Use when: fixing static analysis violations in C or C++ code reported by Parasoft C/C++test"
---

# C/C++test Fix All Violations Skill

This skill fixes Parasoft C/C++test static analysis violations. Code changes can be optionally committed to the repository.

## When to Use This Skill

Use this skill when:
- User wants to fix or repair static analysis violations in C or C++ code

## Assets

This skill uses the following external resources and tools:
| Type | Name | Description | Failure Handling |
| --- | --- | --- | --- |
| MCP Tool | `get_violations_from_report_file` | Fetches violations from a Parasoft C/C++test report file. | Report error and exit |
| MCP Tool | `get_rule_documentation` | Fetches rule documentation from Parasoft C/C++test. | Report warning and proceed |

## Workflow

Overview of the workflow:
- Get the list of violations 
- Select rule to fix
- For selected rule:
    - Print the selected rule header
    - Get rule documentation using the `get_rule_documentation` MCP tool
    - Fix violations
- Repeat workflow until all violations are fixed
- Do not re-run the static analysis at the end of the workflow

Be sure to follow the workflow steps in order. Steps should be executed sequentially, without user intervention, until the final output is generated.

### Step 1: Get the list of violations

**Always** use `get_violations_from_report_file` MCP tool to fetch the list of static analysis violations. 

### Step 2: Prioritize Violations and Select Rule to Fix

From the collected violations, select one rule with the **highest severity**. Severity 1 is the highest, severity 5 is the lowest (1 > 2 > 3 > 4 > 5).

### Step 3: Get Rule Documentation

**Always** use `get_rule_documentation` MCP tool to fetch documentation for the selected rule. This documentation may include the rule description, rationale, examples of compliant and non-compliant code, and guidance on how to fix violations of this rule.

### Step 4: Fix Violations of the Selected Rule

Attempt to fix all violations of the selected rule in a loop. For each violation analyze the violation messages, code, and rule documentation, then make the smallest changes possible to resolve the violations. **Do not** fix violations of other rules.

### Step 5: Repeat for Next Rule

Repeat steps 3-5 until all violations are fixed.