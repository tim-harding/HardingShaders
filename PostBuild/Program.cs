namespace PostBuild 
{
    using System;
    using System.IO;
    using System.Collections;

    /// <summary>
    /// This app just lives alongside the main shader to copy the DLL to its
    /// install location for easier testing.  I would still like to figure
    /// out how to make it fire off an ass test scene after it compiles and
    /// copies, but haven't gotten around to it yet.  Trickier to do without
    /// kick.exe becoming a child process of Visual Studio.  Would have to
    /// set up some sort of server.
    ///
    /// Some of what I'm doing here assumes that you're using Maya and need
    /// to copy the metadata files and python attribute editor template
    /// around.  If those parts are irrelevant to you, they should fail
    /// harmlessly.  
    /// </summary>
    class Program
    {
        static void Main(string[] args)
        {
            string solutionRoot = GetSolutionRoot();
            string pluginPath = GetPluginPath();
            string templatePath = GetTemplatePath();

            const string dll = "HardingShaders.dll";
            string srcDll = Path.Combine(solutionRoot, "x64", "Release", dll);
            string dstDll = Path.Combine(pluginPath, dll);
            CopyFile(srcDll, dstDll);

            foreach (var asset in Assets(Path.Combine(solutionRoot, "Assets")))
            {
                string filename = Path.GetFileName(asset as string);
                string destination;
                switch (Path.GetExtension(filename))
                {
                    case ".mtd":
                        destination = Path.Combine(pluginPath, filename);
                        break;
                    case ".py":
                        destination = Path.Combine(templatePath, filename);
                        break;
                    default:
                        // Unrecognized file type, continues foreach
                        continue;
                }
                CopyFile(asset as string, destination);
            }
        }

        private static IEnumerable Assets(string folder)
        {
            try
            {
                foreach (string directory in Directory.GetDirectories(folder))
                {
                    foreach (string file in Directory.GetFiles(directory))
                    {
                        yield return file;
                    }
                    foreach (string file in Assets(directory))
                    {
                        yield return file;
                    }
                }
            }
            finally { }
        }

        /// <summary>
        /// Attempts to copy from one path to another.  If the copy fails, it
        /// alerts the user on the command line.
        /// </summary>
        /// <param name="from">The source file path</param>
        /// <param name="to">The destination file path</param>
        private static void CopyFile(string from, string to)
        {
            try
            {
                File.Copy(from, to, true);
                string message = String.Format("Copied from \"{0}\" to \"{1}\"", from, to);
                Console.WriteLine(message);
            }
            catch (Exception e)
            {
                string message = String.Format("There was a problem copying \"{0}\" to \"{1}\"", from, to);
                Console.WriteLine(message);
                Console.WriteLine(e.Message);
            }
        }

        /// <summary>
        /// Returns the Visual Studio solution root, e.g.
        /// C:\Users\{user}\Documents\Visual Studio
        /// 2017\Projects\CameraTextureShader\
        /// </summary>
        private static string GetSolutionRoot()
        {
            // GetCurrentDirectory is different depending on whether this is run
            // from the commmand line or as part of the Visual Studio post build
            // process. This is tailored for the latter.
            return Directory.GetParent(Directory.GetCurrentDirectory()).FullName;
        }

        /// <summary>
        /// Returns one of the paths provided by ARNOLD_PLUGIN_PATH, or null if
        /// none exists.  
        /// </summary>
        private static string GetPluginPath()
        {
            string pluginPathVariable = Environment.GetEnvironmentVariable("ARNOLD_PLUGIN_PATH", EnvironmentVariableTarget.User);
            if (pluginPathVariable == null)
            {
                Console.WriteLine("Did you set ARNOLD_PLUGIN_PATH?");
                return null;
            }

            string[] pluginPaths = pluginPathVariable.Split(';');
            string path = "";
            if (pluginPaths.Length == 1)
            {
                path = pluginPaths[0];
            }
            else
            {
                // If multiple paths are found, one with 'bin' at the end
                // of the name. This allows separate paths for OSL and CPP plugins.
                bool didFindBin = false;
                foreach (string pluginPath in pluginPaths)
                {
                    string[] pieces = pluginPath.Split(Path.DirectorySeparatorChar);
                    if (pieces[pieces.Length - 1] == "bin")
                    {
                        path = pluginPath;
                        didFindBin = true;
                        break;
                    }
                }

                path = didFindBin ? path : pluginPaths[0];
            }

            return path;
        }

        /// <summary>
        /// Returns the MTOA_TEMPLATES_PATH environment variable.  For Maya
        /// users. Unlike GetPluginPath, this assumes only one path is stored
        /// there. 
        /// </summary>
        private static string GetTemplatePath()
        {
            string templatePathVariable = Environment.GetEnvironmentVariable("MTOA_TEMPLATES_PATH", EnvironmentVariableTarget.User);
            if (templatePathVariable == null)
            {
                Console.WriteLine("Did you set MTOA_TEMPLATES_PATH?");
                templatePathVariable = "";
            }
            return templatePathVariable;
        }
    }
}
