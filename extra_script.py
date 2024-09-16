import os
Import("env")


def update_ccls(*args, **kwargs):
    print("Update .ccls file")

    # Path to the .ccls file (set this as per your project structure)
    ccls_file_path = os.path.join(env['PROJECT_DIR'], '.ccls')

    # Read the existing .ccls content
    if os.path.exists(ccls_file_path):
        with open(ccls_file_path, 'r') as file:
            existing_lines = set(line.strip() for line in file.readlines())
    else:
        existing_lines = set()

    # Get project configuration
    config = env.GetProjectConfig()
    lib_dirs = config.get("platformio", "libdeps_dir")

    # Gather include directories
    includes_to_add = []
    for scope, includes in env.DumpIntegrationIncludes().items():
        if scope == 'build':
            for include_dir in includes:
                if include_dir.startswith(lib_dirs):
                    include_flag = f"-I{include_dir}"
                    if include_flag not in existing_lines:
                        includes_to_add.append(include_flag)

    # Update .ccls file only if there are new includes to add
    if includes_to_add:
        with open(ccls_file_path, 'a') as file:
            for include in includes_to_add:
                file.write(f"{include}\n")
            print(f"Added {len(includes_to_add)} include directories to {ccls_file_path}")
    else:
        print("No new include directories to add.")


# Add the custom target to PlatformIO
env.AddCustomTarget("update_ccls", None, update_ccls)
