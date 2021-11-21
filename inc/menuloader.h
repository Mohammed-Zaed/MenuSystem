#include <iostream>
#include <cstring>

template <unsigned int size, unsigned int titleLength>
class MenuLoader : public iMenu
{
    public:
        MenuLoader (const char* headerText)
        : m_maxNumOfPages(size),
          m_pageCounter(0U),
          m_currentPage(0U)
        {
            std::memcpy(m_headerText, headerText, titleLength + 1U);
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
            std::cout << m_headerText << std::endl;

            if (isPageValid())
            {
                m_menuList[m_currentPage]->display();
            }

            //Menu handling information
            std::cout << "Press 'n' for next page" << std::endl;
            std::cout << "Press 'p' for previous page" << std::endl;
            std::cout << "Press 'q' for quitting" << std::endl;
            std::cout << "Page : " << +m_currentPage << " of " << +m_pageCounter << std::endl;
        }

        virtual bool
        handle (uint8_t command)
        {
            bool isSuccess = m_menuList[m_currentPage]->handle(command);

            if (false == isSuccess)
            {
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

        char    m_headerText[titleLength + 1];   // +1U for extra null character

        iMenu* m_menuList[size];
};
