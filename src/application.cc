#include <application.h>

#include <iostream>

namespace gle
{

/* ************************ Application::Application *********************** */

Application::Application (int argc, char **argv)
{
  parse_arguments (argc, argv);

  // TODO : Further application init
}

/* ********************** Application::parse_arguments ********************* */

void
Application::parse_arguments (int argc, char **argv)
{
  int n = 0;
  std::string arg;
  std::string lname;
  std::string value;
  char sname;

  if (argc <= 1)
    return;

  std::string::const_iterator it;

  while (true)
    {
      n++;
      if (n >= argc)
        break;

      arg = argv[n];
      it = arg.begin ();
      lname.clear ();
      value.clear ();

      // Check for -
      if (*it != '-')
        continue;
      // Check wether argument is short or long
      it++;
      if (*it == '-') // Long argument
        {
          it++;
          while (*it != '=') // Extract name
            {
              if (it == arg.end ())
                break;
              else
                lname.push_back (*it);
              it++;
            }

          if (it != arg.end ())
            it++;          // Skip =
          if (*it == '\"') // Skip open "
            it++;
          while (it != arg.end ()) // Extract value
            {
              value.push_back (*it);
              it++;
            }
          if (!value.empty ()
              && value[value.size () - 1] == '\"') // Remove close "
            value.pop_back ();
          std::cout << "emplace_back(" << lname << ", " << value << ")" << std::endl;
          m_args.emplace_back (lname, value);
        }
      else // Short argument
        {
          sname = *it;
          it++;
          if (it != arg.end ())
            {
              while (it != arg.end ()) // Extract value
                {
                  value.push_back (*it);
                  it++;
                }
            }
          else
            {
              n++;
              if (n >= argc)
                value = "";
              else
                value = argv[n];
              std::cout << "emplace_back(" << sname << ", " << value << ")" << std::endl;
              m_args.emplace_back (sname, value);
            }
        }
    }
}

/* **************************** Application::run *************************** */

int
Application::run ()
{
  return 0;
}

} // namespace gle
