#include <iostream>
#include <stdint.h>

class iMenu 
{
    public:
        virtual void display() = 0;
        virtual bool handle(uint8_t command) = 0;
};


class FirstMenu : public iMenu
{
    public:
        virtual void display() { std::cout << "First Menu" << std::endl; }
        virtual bool handle(uint8_t command) { std::cout << "First Menu handler" << std::endl; return false;}
};

class SecondMenu : public iMenu
{
    public:
        virtual void display() { std::cout << "Second Menu" << std::endl; }
        virtual bool handle(uint8_t command) { std::cout << "Second Menu handler" << std::endl; return false;}
};

template <unsigned int size>
class MenuLoader : public iMenu
{
    public:
        MenuLoader ()
        : m_maxNumOfPages(size),
          m_pageCounter(0U),
          m_currentPage(0U)
        {
            std::cout << "Num of Pages in menu: " << size << std::endl;
        };

        virtual 
        ~MenuLoader ()
        {

        }

        void
        addMenu (iMenu* menu)
        {
            if (!isListFull())
            {
                m_menuList[m_pageCounter] = menu;
                ++m_pageCounter;
            }
            else
            {
                std::cout << "Menu > Error : Cannot be added, list full" << std::endl;
            }
        }

        virtual void
        display ()
        {
            if (isPageValid())
            m_menuList[m_currentPage]->display();

            //Menu handling information
            std::cout << "Press 'n' for next page" << std::endl;
            std::cout << "Press 'p' for previous page" << std::endl;
            std::cout << "Press 'q' for quitting" << std::endl;
            std::cout << "Page : " << +m_currentPage << " of " << +m_pageCounter << std::endl;
        }

        virtual bool
        handle (uint8_t command)
        {
            std::cout << "User input : " << command << std::endl;

            bool isSuccess = m_menuList[m_currentPage]->handle(command);

            std::cout << "isSuccess : " << isSuccess << std::endl;

            if (false == isSuccess)
            {
                std::cout << "Handle in Menu loader" << std::endl;

                switch (command)
                {
                    case 'n' :
                    {
                        next();
                        isSuccess = true;
                    }
                    break;

                    case 'p' :
                    {
                        previous();
                        isSuccess = true;
                    }
                    break;

                    case 'q' :
                    {
                        isSuccess = false;
                    }
                    break;

                    default :
                    {
                        std::cout << "Invalid choice" << std::endl;
                        isSuccess = true;
                    }
                    break;
                }

                
            }

            return isSuccess;
        }

        void 
        next ()
        {
            goToNextPage();
            display();
        }

        void 
        previous ()
        {
            goToPreviousPage();
            display();
        }

    private:
        bool
        isPageValid () const
        {
            return (m_pageCounter > 0) && (m_pageCounter < m_maxNumOfPages); 
        }

        bool
        isListFull () const
        {
            return !((m_pageCounter >= 0) && (m_pageCounter < m_maxNumOfPages));
        }

        void
        goToNextPage ()
        {
            m_currentPage = ++m_currentPage % m_pageCounter;
        }

        void
        goToPreviousPage ()
        {
            m_currentPage = --m_currentPage % m_pageCounter;
        }


    private:
        const uint8_t m_maxNumOfPages;

        uint8_t m_pageCounter;
        uint8_t m_currentPage;

        iMenu* m_menuList[size];
};


int 
main ()
{
    FirstMenu firstMenu;
    SecondMenu SecondMenu;

    MenuLoader <10> menuLoader;

    menuLoader.addMenu(&firstMenu);
    menuLoader.addMenu(&SecondMenu);

    bool isContinue = true;
    while (isContinue)
    {
        menuLoader.display();
        uint8_t cmd = 0;
        std::cin >> cmd;
        isContinue = menuLoader.handle(cmd);

    }
    
    return 0;
}