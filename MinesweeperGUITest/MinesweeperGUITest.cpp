#include "pch.h"
#include "CppUnitTest.h"
#include <cstring>
#include<thread>
#include<chrono>
#include "../MinesweeperGUI/include/game_enums.hpp"
#include "../MinesweeperGUI/include/game.hpp"
#include "../MinesweeperGUI/include/gui.hpp"
#include "../MinesweeperGUI/include/ranklist.hpp"
#include "../MinesweeperGUI/include/GUI/dir.hpp"
#include<filesystem>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace gui;
using namespace minesweeper;

namespace MinesweeperGUITest
{
	TEST_CLASS(gui_test)
	{
	public:
		
		TEST_METHOD(widget_click_test)
		{
			auto* g = new scene(1280, 720);
			label* arr[100];
			int* test_flag = new int(0);
			for (auto& i : arr)
			{
				i = new label(0, 0, 10, 10);
				g->add_widget(i);
				i->on_click([test_flag](auto* args)
					{
						(*test_flag)++;
					});
			}
			auto* args = new mouse_event_args({ 1,1 }, state_keydown, state_keydown, state_keydown, {0,0});
			args->click_flags = mouse_left;
			auto e = event(args, event_mouse_click);
			g->event_dispatch(e);
			Assert::AreEqual(*test_flag, 100);
			delete test_flag;
			for (auto& i : arr)
			{
				delete i;
			}
			delete g;
		}

		TEST_METHOD(widget_remove_test)
		{
			auto* g = new scene(1280, 720);
			label* arr[100];
			int* test_flag = new int(0);
			for (auto& i : arr)
			{
				i = new label(0, 0, 10, 10);
				g->add_widget(i);
				i->on_click([test_flag](auto* args)
					{
						(*test_flag)++;
					});
			}
			for (auto& i : arr)
			{
				i->remove_from_parent();
			}
			auto* args = new mouse_event_args({ 1,1 }, state_keydown, state_keydown, state_keydown, { 0,0 });
			args->click_flags = mouse_left;
			auto e = event(args, event_mouse_click);
			g->event_dispatch(e);
			Assert::AreEqual(*test_flag, 0);
			delete test_flag;
			for(int i=0;i<99;i++)
			{
				delete arr[i];
			}
			delete g;
			delete arr[99];
		}

		TEST_METHOD(form_settings)
		{
			constexpr int test_fps = 123;
			constexpr int test_pos_x = 20;
			constexpr int test_pos_y = 30;
			auto& f = form::get_instance();
			auto* s = new scene(1280, 720);
			f.current_scene = s;
			f.set_title("1234").set_fps(test_fps).resize(1200, 900);
			Assert::AreEqual(strcmp(f.get_title(), "1234"),0);
			Assert::IsTrue(f.is_initialized()==false);
			f.show();
			f.set_pos(test_pos_x, test_pos_y);
			Assert::IsTrue(f.is_initialized());
			Assert::IsTrue(GetFPS()<=test_fps);
			Assert::IsTrue(static_cast<int>(GetWindowPosition().x)==test_pos_x);
			Assert::IsTrue(static_cast<int>(GetWindowPosition().y)==test_pos_y);
			f.draw_once();
			f.close();
			CloseWindow();
			Assert::IsFalse(f.is_initialized());
		}

		TEST_METHOD(event_trigger_in_nested_groups)
		{
			auto& f = form::get_instance().set_fps(60).resize(1280,720);
			auto* s = new scene(1280, 720);
			f.current_scene = s;
			auto* test_flag = new int(0);
			group* groups[10];
			for (auto& i : groups)
			{
				i = new group(0, 0, 1280, 720);
			}
			for(int i=1;i<10;i++)
			{
				groups[i - 1]->add_widget(groups[i]);
			}
			auto* b = new button(0, 0, 100, 100);
			groups[9]->add_widget(b);
			b->on_click([&](auto* args)
				{
					(*test_flag)++;
				});
			s->add_widget(groups[0]);
			f.show();
			auto args = mouse_event_args({ 0,0 }, state_keydown, state_keydown, state_keydown, { 0,0 });
			args.click_flags = 0b111;
			event e = event(&args,event_mouse_click);
			event_queue.push(e);
			f.draw_once();
			Assert::AreEqual(*test_flag, 1);
		}
		

	};
	TEST_CLASS(ranklist_test)
	{
		static void complete_game(minesweeper::game& g, std::chrono::duration<unsigned long long, std::milli> duration)
		{
			using namespace std::chrono_literals;
			for (int i = 1; i <= g.rows; i++)
			{
				for (int j = 1; j <= g.cols; j++)
				{
					if (g.usermap[i][j] == UNKNOWN)
					{
						switch (g.map[i][j])
						{
						case MINE:
							break;
						default:
							g.click_handler(j, i, CLK_LEFT);
							std::this_thread::sleep_for(duration);
						}
					}
				}
			}
		}

		TEST_METHOD(ranklist_save_easy)
		{
			game g = game(9, 9, 10);
			g.win_hook = [](auto& _)
			{
				gui::util::dir::set_exec_dir((std::filesystem::current_path().string() + "\\Debug").c_str());
				playermsg m_msg = playermsg();
				m_msg.score = _.timer.get_elapsed_time();
				auto m_ranklist = ranklist(DIFFICULTY_EASY);
				m_ranklist.savemsg(m_msg);
			};
			g.lose_hook = [](auto&)
			{
				Assert::Fail();
			};
			g.update_hook = [](auto, auto, auto) {};
			g.click_handler(1, 1, CLK_LEFT);
			complete_game(g, std::chrono::duration<unsigned long long, std::milli>(10));
		}

		TEST_METHOD(ranklist_save_mid)
		{
			game g = game(16, 16, 40);
			g.win_hook = [](auto& _)
			{
				gui::util::dir::set_exec_dir((std::filesystem::current_path().string() + "\\Debug").c_str());
				playermsg m_msg = playermsg();
				m_msg.score = _.timer.get_elapsed_time();
				auto m_ranklist = ranklist(DIFFICULTY_MEDIUM);
				m_ranklist.savemsg(m_msg);
			};
			g.lose_hook = [](auto&)
			{
				Assert::Fail();
			};
			g.update_hook = [](auto, auto, auto) {};
			g.click_handler(1, 1, CLK_LEFT);
			complete_game(g, std::chrono::duration<unsigned long long, std::milli>(10));
		}

		TEST_METHOD(ranklist_save_hard)
		{
			game g = game(30, 16, 99);
			g.win_hook = [](auto& _)
			{
				gui::util::dir::set_exec_dir((std::filesystem::current_path().string() + "\\Debug").c_str());
				playermsg m_msg = playermsg();
				m_msg.score = _.timer.get_elapsed_time();
				auto m_ranklist = ranklist(DIFFICULTY_HARD);
				m_ranklist.savemsg(m_msg);
			};
			g.lose_hook = [](auto&)
			{
				Assert::Fail();
			};
			g.update_hook = [](auto, auto, auto) {};
			g.click_handler(1, 1, CLK_LEFT);
			complete_game(g, std::chrono::duration<unsigned long long, std::milli>(10));
		}

		TEST_METHOD(ranklist_mid_read)
		{
			gui::util::dir::set_exec_dir((std::filesystem::current_path().string() + "\\Debug").c_str());
			auto r = ranklist(DIFFICULTY_MEDIUM);

		}
	};
}
