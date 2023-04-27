#include <application.h>
#include <logger.h>

#include <iostream>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H

namespace gle
{

/* ************************ Application::Application *********************** */

Application::Application (int argc, char **argv) : m_should_close (true)
{
  parse_arguments (argc, argv);

  // TODO : Further application init

  m_should_close = false;
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
          m_args.emplace_back (lname, 0, value);
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
              else if (argv[n][0] == '-')
                n--;
              else
                value = argv[n];
              m_args.emplace_back ("", sname, value);
            }
        }
    }
}

/* **************************** Application::run *************************** */

int
Application::run ()
{
  for (auto it : m_args)
    {
      if (it.get_long_name () == "--help" || it.get_short_name () == "-h")
        usage ();
      if (it.get_long_name () == "--version" || it.get_short_name () == "-v")
        version ();
    }

  if (m_should_close)
    return 0;

  // TODO : Run the application

  return 0;
}

/* *********************** Application::register_arg *********************** */

void
Application::register_arg (char sname, const std::string &lname,
                           const std::string &comment)
{
  m_accepted_args.emplace_back(lname, sname, comment, "");
}

/* *************************** Application::usage ************************** */

void
Application::usage ()
{
  std::cout << "Usage: " << PACKAGE << " [options]" << std::endl;
  std::cout << "Options:" << std::endl;
  std::cout.flush();
  for (auto it : m_accepted_args)
    {
      std::cout << "  " << it.get_long_name ();
      std::cout << ", " << it.get_short_name ();
      std::cout << "  " << it.get_comment () << std::endl;
    }
}

/* ************************** Application::version ************************* */

void
Application::version ()
{
  std::cout << PACKAGE << " " << VERSION << std::endl;
}

} // namespace gle
